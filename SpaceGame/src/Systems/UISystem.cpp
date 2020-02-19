#include "UISystem.h"
#include "AEEngine.h"
#include "../ECS/Core.h"
#include "../Components/cUIElement.h"
#include "../Components/cTransform.h"
#include "../Managers/ResourceManager.h"				//FontId


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
		
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_NONE);
		AEGfxSetTransparency(1.0f);

		Console_Cout(uiComponent->_text);
		AEGfxPrint(ResourceManager::fontId, uiComponent->_text,
			static_cast<int>(uiTransform->_position.x), static_cast<int>(uiTransform->_position.y), 1.0f, 0.0f, 0.0f);
	}
}

void UISystem::EditText(ENTITY target, const char* newText)
{
	AE_ASSERT(entitiesList.find(target) != entitiesList.end() && "UI not found");

	cUIElement* uiComponent = Core::Get().GetComponent<cUIElement>(target);
	sprintf_s(uiComponent->_text, newText);
}