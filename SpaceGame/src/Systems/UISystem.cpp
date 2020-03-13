#include "UISystem.h"
#include "AEEngine.h"
#include "../ECS/Core.h"
#include "../Components/cUIElement.h"
#include "../Components/cTransform.h"
#include "../Components/cSprite.h"
#include "../Managers/ResourceManager.h"				//FontId
#include "../Math/Math.h"								//lerping
#include "../Global.h"									//Screen size
#include "../Managers/GameStateManager.h"
#include "../ECS/Factory.h"								//Create enemy indicator...careful of circular dependency

#include "../Tools/Console.h"
void UISystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cUIElement>());
	Core::Get().SetSystemSignature<UISystem>(signature);

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
				AEVec2Set(&textPosition, uiTransform->_position.x - (14.5f * uiComponent->_text._bufferCount/2)
					, uiTransform->_position.y - 8);
			}

			AEGfxPrint(ResourceManager::fontId, uiComponent->_text._textBuffer,
				static_cast<int>(textPosition.x), static_cast<int>(textPosition.y),
				uiComponent->_text._colorTint.r, uiComponent->_text._colorTint.g, uiComponent->_text._colorTint.b);
		}
		
	}
}

void UISystem::EditText(ENTITY target, const char* newText)
{
	AE_ASSERT(entitiesList.find(target) != entitiesList.end() && "UI not found");

	cUIElement* uiComponent = Core::Get().GetComponent<cUIElement>(target);
	sprintf_s(uiComponent->_text._textBuffer, newText);
	uiComponent->_text._bufferCount = strlen(newText);
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

int globalHealth = 30;

bool OnHealthChange_HPUI(ENTITY entity, Events::OnHealthChange* message)
{
	cSprite* sprite = Core::Get().GetComponent <cSprite>(entity);
	cUIElement* uiComp = Core::Get().GetComponent <cUIElement>(entity);

	globalHealth = static_cast<int>(MBMath_Lerp(static_cast<float>(globalHealth), message->_newHealth, 1.0f));
	printf("globalHealth %d entity %d \n", globalHealth, uiComp->_roleIndex);
	if (globalHealth / 10 > uiComp->_roleIndex)
	{
		sprite->_UVOffset.x = 0.0f;
	}
	else if (globalHealth / 10 == uiComp->_roleIndex)
	{
		sprite->_UVOffset.x = 0.5f * (10 - (globalHealth % 10))/10;

	}
	else if (globalHealth / 10 < uiComp->_roleIndex)
	{
		sprite->_UVOffset.x = 0.5f;
	}

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

void UISystem::Check_AIIndicatorExist(ENTITY ai, AEVec2 aiDir)
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

			return;
		}
	}
	Factory_UI::Create_AIIndicator(ai, aiDir);
}

void UISystem::OnComponentAdd(ENTITY entity)
{
	cUIElement* uiComp = Core::Get().GetComponent<cUIElement>(entity);

	switch (uiComp->_role)
	{
		case UI_ROLE::INDICATE_AI:
			aiIndicator_Set.insert(entity);
			break;
	}
}
