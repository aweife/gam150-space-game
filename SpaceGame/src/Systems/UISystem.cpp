#include "UISystem.h"
#include "AEEngine.h"
#include "../ECS/Core.h"
#include "../Components/cUIElement.h"
#include "../Components/cTransform.h"
#include "../Components/cSprite.h"
#include "../Managers/ResourceManager.h"				//FontId
#include "../Math/Math.h"								//Lerping
#include "../Global.h"									//Screen size
#include "../Managers/GameStateManager.h"
#include "../ECS/Factory.h"								//Create enemy indicator...careful of circular dependency
#include "../Player/PlayerManager.h"

#include "../Tools/Console.h"
#include "../Tools/Editor.h"
void UISystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cUIElement>());
	Core::Get().SetSystemSignature<UISystem>(signature);

}
void UISystem::Update()
{
	const ENTITY pid = PlayerManager::player;
	if (pid == 0) return;
	cUIElement* uiComp;
	cTransform* transform;

	//Enemy indicator update - Check if the enemy is still calling it (Still OOB)
	//Otherwise destroy it
	for (std::set<ENTITY>::const_iterator it = aiIndicator_Set.begin(); it != aiIndicator_Set.end(); )
	{
		uiComp = Core::Get().GetComponent<cUIElement>(*it);
		//if indicator is no longer being used..delete it
		if (!uiComp->_isActive)		
		{
			ENTITY destroy = *it;
			++it;									//Avoid iterator invalidation
			Core::Get().EntityDestroyed(destroy);
		}
		else
		{
			uiComp->_isActive = false;				//reset for next frame
			++it;
		}
	}

	for (std::set<ENTITY>::const_iterator it = shieldBubble_Set.begin(); it != shieldBubble_Set.end(); ++it)
	{
		uiComp = Core::Get().GetComponent<cUIElement>(*it);
		if (uiComp->_isActive)
		{
			transform = Core::Get().GetComponent<cTransform>(*it);
			transform->_position.x = Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position.x;
			transform->_position.y = Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position.y;

		}
	}
}
void UISystem::Render()
{
	cUIElement* uiComponent;
	cTransform* uiTransform;

	for (auto const& entity : entitiesList)
	{
		uiComponent = Core::Get().GetComponent<cUIElement>(entity);
		uiTransform = Core::Get().GetComponent<cTransform>(entity);
		
		if (uiComponent->_type == UI_TYPE::TEXT)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
			AEGfxSetTransparency(uiComponent->_text._colorTint.a);

			AEVec2 textPosition = { 0 };
			if (uiComponent->_text._anchor == TEXT_ANCHOR::CENTERLEFT)
			{
				AEVec2Set(&textPosition, uiTransform->_position.x - (uiTransform->_scale.x * 0.5f), uiTransform->_position.y - 8);
			}
			else if(uiComponent->_text._anchor == TEXT_ANCHOR::CENTERRIGHT)
			{
				AEVec2Set(&textPosition, uiTransform->_position.x + (uiTransform->_scale.x * 0.5f)
					- (14.5f * uiComponent->_text._bufferCount), uiTransform->_position.y - 8) ;
			}
			else if (uiComponent->_text._anchor == TEXT_ANCHOR::CENTER)
			{
				AEVec2Set(&textPosition, uiTransform->_position.x - (14.0f * uiComponent->_text._bufferCount/2)
					, uiTransform->_position.y - 8);
			}

			AEGfxPrint(ResourceManager::fontId, uiComponent->_text._textBuffer,
				static_cast<int>(textPosition.x), static_cast<int>(textPosition.y),
				uiComponent->_text._colorTint.r, uiComponent->_text._colorTint.g, uiComponent->_text._colorTint.b);
		}
		
	}
}

void EditText(ENTITY target, const char* newText)
{
	cUIElement* uiComponent = Core::Get().GetComponent<cUIElement>(target);
	if (!uiComponent) return;
	sprintf_s(uiComponent->_text._textBuffer, newText);
	uiComponent->_text._bufferCount = strlen(newText);
}

void EditText(ENTITY target, const char* newText, int atBack)
{
	cUIElement* uiComponent = Core::Get().GetComponent<cUIElement>(target);
	if (!uiComponent) return;
	char buffer[200] = { 0 };
	char intBuffer[5] = { 0 };
	sprintf_s(intBuffer, "%d", atBack);
	strcat_s(buffer, newText);
	strcat_s(buffer, intBuffer);

	sprintf_s(uiComponent->_text._textBuffer, buffer);
	uiComponent->_text._bufferCount = strlen(buffer);
}

//Percentage upon 1.0f
AEVec2 ScreenBasedCoords(float x, float y, UI_ANCHOR anchor, bool percentage)
{
	AEVec2 screenVector;
	AEVec2Set(&screenVector, 0.0f, 0.0f);
	switch (anchor)
	{
		case UI_ANCHOR::CENTER:
			if (percentage)
				AEVec2Set(&screenVector, g_WorldMaxX * x, g_WorldMaxY * y);
			else
				AEVec2Set(&screenVector, x, y);
			break;
		case UI_ANCHOR::TOPLEFT:
			if (percentage)
				AEVec2Set(&screenVector, g_WorldMaxX * 2 * (x-0.5f), g_WorldMaxY * 2 * (y + 0.5f));
			else
				AEVec2Set(&screenVector, x - g_WorldMaxX , g_WorldMaxY + y);
			break;
		case UI_ANCHOR::TOPRIGHT:
			if (percentage)
				AEVec2Set(&screenVector, g_WorldMaxX * 2 * (x + 0.5f), g_WorldMaxY * 2 * (y + 0.5f));
			else
				AEVec2Set(&screenVector, x + g_WorldMaxX , g_WorldMaxY + y);
			break;
		case UI_ANCHOR::BOTTOMLEFT:
			if (percentage)
				AEVec2Set(&screenVector, g_WorldMaxX * 2 * (x - 0.5f), g_WorldMaxY * 2 * (y - 0.5f));
			else
				AEVec2Set(&screenVector, x - g_WorldMaxX , y - g_WorldMaxY);
			break;
		case UI_ANCHOR::BOTTOMRIGHT:
			if (percentage)
				AEVec2Set(&screenVector, g_WorldMaxX * (x + 0.5f), g_WorldMaxY * 2 * (y - 0.5f));
			else
				AEVec2Set(&screenVector, x + g_WorldMaxX , y - g_WorldMaxY);
			break;
	}
	return screenVector;
}


bool OnHealthChange_HPUI(ENTITY entity, Events::OnHealthChange* message)
{
	cSprite* sprite = Core::Get().GetComponent <cSprite>(entity);
	cUIElement* uiComp = Core::Get().GetComponent <cUIElement>(entity);

	unsigned int tenths = static_cast<int>(message->_newHealth) / 10;

	if (tenths > uiComp->_roleIndex)
	{
		sprite->_UVOffset.x = 0.0f;
	}
	else if (tenths == uiComp->_roleIndex)
	{
		sprite->_UVOffset.x = 0.5f * (10 - (static_cast<int>(message->_newHealth) % 10))/10;

	}
	else if (tenths < uiComp->_roleIndex)
	{
		sprite->_UVOffset.x = 0.5f;
	}

	return true;
}

bool OnShieldChange_ShieldUI(ENTITY entity, Events::OnShieldChange* message)
{
	cSprite* sprite = Core::Get().GetComponent <cSprite>(entity);
	cUIElement* uiComp = Core::Get().GetComponent <cUIElement>(entity);

	unsigned int tenths = static_cast<int>(message->_newShield) / 10;

	if (tenths > uiComp->_roleIndex)
	{
		sprite->_UVOffset.x = 0.0f;
	}
	else if (tenths == uiComp->_roleIndex)
	{
		sprite->_UVOffset.x = 0.5f * (10 - (static_cast<int>(message->_newShield) % 10)) / 10;

	}
	else if (tenths < uiComp->_roleIndex)
	{
		sprite->_UVOffset.x = 0.5f;
	}

	return true;
}

bool OnShieldActivate_ShieldBubble(ENTITY entity, Events::OnShieldActivate* message)
{
	UNREFERENCED_PARAMETER(message);
	cUIElement* uiComp = Core::Get().GetComponent<cUIElement>(entity);
	if (!uiComp->_isActive)
	{
		uiComp->_isActive = true;

		//Create a shield that fades out after 1.5s
		Core::Get().AddComponent<cTimeline>(entity, new cTimeline(g_appTime, g_appTime + 1.5f, false));
		AddNewTimeline_Float(&Core::Get().GetComponent<cSprite>(entity)->_colorTint.a, Core::Get().GetComponent<cTimeline>(entity));
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(entity)->_colorTint.a, Core::Get().GetComponent<cTimeline>(entity), 0.50f, 1.0f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(entity)->_colorTint.a, Core::Get().GetComponent<cTimeline>(entity), 1.00f, 1.0f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(entity)->_colorTint.a, Core::Get().GetComponent<cTimeline>(entity), 1.49f, 0.0f);
		//Set the shield to inactive after fading out
		AddNewTimeline_Bool(&Core::Get().GetComponent<cUIElement>(entity)->_isActive, Core::Get().GetComponent<cTimeline>(entity));
		AddNewNode_Bool(&Core::Get().GetComponent<cUIElement>(entity)->_isActive, Core::Get().GetComponent<cTimeline>(entity), 1.5f, false);
	}
	return true;			//successfuly execution
}

bool OnThrusterChange_ThrusterUI(ENTITY entity, Events::OnThrusterChange* message)
{
	float percentage = (message->_newVelocity - 75.0f)/ (message->_capVelocity - 75.0f);
	percentage = MBMath_Clamp(percentage, 0.0f, 5/8.0f);
	percentage += (message->_overheatTime / message->_overheatLimit) * 3 /8.0f;

	Editor_TrackVariable("Percentage", percentage);

	cSprite* sprite = Core::Get().GetComponent<cSprite>(entity);
	sprite->_UVOffset.y = percentage * -0.5f;
	//Overheat
	sprite->_colorTint.g = 1.0f - (message->_overheatTime / message->_overheatLimit);
	return true;
}

bool OnButtonClick_MainMenuUI(ENTITY entity, Events::OnMouseClick* message)
{
	cTransform* transform = Core::Get().GetComponent<cTransform>(entity);
	
	float buttomMaxX = transform->_position.x + transform->_scale.x / 2;
	float buttomMaxY = transform->_position.y + transform->_scale.y / 2;
	float buttomMinX = transform->_position.x - transform->_scale.x / 2;
	float buttomMinY = transform->_position.y - transform->_scale.y / 2;

	//printf("mouse %f %f \n", message->_xPos, message->_yPos);
	//printf("orig %f %f \n", transform->_position.x, transform->_position.y);
	//printf("min %f %f \n", buttomMinX, buttomMinY);
	//printf("max %f %f \n", buttomMaxX, buttomMaxY);
	if ((buttomMaxX > message->_xPos && buttomMinX < message->_xPos &&
		buttomMaxY > message->_yPos && buttomMinY < message->_yPos) == false)
	{
		//printf("failed\n");
		return false;
	}
	GSM_LoadingTransition(GS_LEVEL1);
	return true;
}

void UISystem::Check_AIIndicatorExist(ENTITY ai, AEVec2 aiDir, int aiType)
{
	cUIElement* uiComp = nullptr;
	cTransform* uiTrans = nullptr;

	for(ENTITY entity :aiIndicator_Set)
	{
		uiComp = Core::Get().GetComponent<cUIElement>(entity);
		if (uiComp->_roleIndex == ai)			//the indicator already exists
		{
			//Update the position
			uiTrans = Core::Get().GetComponent<cTransform>(entity);
			float screenGradiant = g_WorldMaxY / g_WorldMaxX;
			AEVec2 aiDir_Normalise;
			AEVec2Normalize(&aiDir_Normalise, &aiDir);

			if (aiDir.x < FLT_EPSILON && aiDir.x > -FLT_EPSILON) //Horizontal axis
			{
				aiDir.x = aiDir_Normalise.x * (g_WorldMaxY / fabs(aiDir_Normalise.y)) * 0.9f;
				aiDir.y = aiDir_Normalise.y * (g_WorldMaxY / fabs(aiDir_Normalise.y)) * 0.9f;
			}
			else if (aiDir.y < FLT_EPSILON && aiDir.y > -FLT_EPSILON) //Vertical axis
			{
				aiDir.x = aiDir_Normalise.x * (g_WorldMaxX / fabs(aiDir_Normalise.x)) * 0.9f;
				aiDir.y = aiDir_Normalise.y * (g_WorldMaxX / fabs(aiDir_Normalise.x)) * 0.9f;
			}
			else
			{
				float aiGradiant = aiDir.y / aiDir.x;
				if (fabs(aiGradiant) < screenGradiant)		//Vertical Axis
				{
					aiDir.x = aiDir_Normalise.x * (g_WorldMaxX / fabs(aiDir_Normalise.x)) * 0.9f;
					aiDir.y = aiDir_Normalise.y * (g_WorldMaxX / fabs(aiDir_Normalise.x)) * 0.9f;
				}
				else if (fabs(aiGradiant) > screenGradiant)	//Horizontal Axis
				{
					aiDir.x = aiDir_Normalise.x * (g_WorldMaxY / fabs(aiDir_Normalise.y)) * 0.9f;
					aiDir.y = aiDir_Normalise.y * (g_WorldMaxY / fabs(aiDir_Normalise.y)) * 0.9f;
				}
			}
			//Calculate angle
			float angle = atan2f(aiDir.y, aiDir.x);

			uiTrans->_position.x = aiDir.x;
			uiTrans->_position.y = aiDir.y;
			uiTrans->_rotation = angle;
			uiComp->_isActive = true;
			return;
		}
	}
	Factory_UI::Create_AIIndicator(ai, aiDir, aiType);
}

void UISystem::DeleteUpgradeWindow()
{
	while (choose3_Set.size() > 0)
	{
		Core::Get().EntityDestroyed(*choose3_Set.begin());
	}
}

void UISystem::OnComponentAdd(ENTITY entity)
{
	cUIElement* uiComp = Core::Get().GetComponent<cUIElement>(entity);

	switch (uiComp->_role)
	{
		case UI_ROLE::INDICATE_AI:
			aiIndicator_Set.insert(entity);
			break;
		case UI_ROLE::C3_FAKEUPGRADE:
		case UI_ROLE::C3_FRAME:
		case UI_ROLE::C3_TEXT:
		case UI_ROLE::C3_UPGRADE:
			choose3_Set.insert(entity);
			break;
		case UI_ROLE::GAMEOVER:
			gameOver_Set.insert(entity);
			break;
		case UI_ROLE::SHIELDBUBBLE:
			shieldBubble_Set.insert(entity);
			break;
	}
}

void UISystem::OnComponentRemove(ENTITY entity)
{
	cUIElement* uiComp = Core::Get().GetComponent<cUIElement>(entity);

	switch (uiComp->_role)
	{
	case UI_ROLE::INDICATE_AI:
		aiIndicator_Set.erase(entity);
		break;
	case UI_ROLE::C3_FAKEUPGRADE:
	case UI_ROLE::C3_FRAME:
	case UI_ROLE::C3_TEXT:
	case UI_ROLE::C3_UPGRADE:
		choose3_Set.erase(entity);
		break;
	case UI_ROLE::GAMEOVER:
		gameOver_Set.erase(entity);
		break;
	case UI_ROLE::SHIELDBUBBLE:
		shieldBubble_Set.erase(entity);
		break;
	}
}
