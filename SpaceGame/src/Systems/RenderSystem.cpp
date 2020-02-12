#include "RenderSystem.h"
#include "AEEngine.h"
#include "../ECS/Core.h"
#include "../Components/cTransform.h"
#include "../Components/cSprite.h"

#include "../Components/cSprite.h"
#include "../Components/cTransform.h"
void RenderSystem::Init()
{
}

void RenderSystem::Update()
{
	// Update all entities that has the components we want
	for (auto const& entity : entitiesList)
	{
		auto const& transform = coreInstance.GetComponent<cTransform>(entity);
		auto const& sprite = coreInstance.GetComponent<cSprite>(entity);

		// Set blend mode to blend so we can render transparency
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);

		// Use textures
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

		// Render at position
		AEGfxSetPosition(transform.position.x, transform.position.y);

		// Position texture
		AEGfxTextureSet(sprite.texture, 0, 0);

		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

		AEGfxSetTransparency(1.0f);

		//Draw
		AEGfxMeshDraw(sprite.mesh, AE_GFX_MDM_TRIANGLES);
	}
}