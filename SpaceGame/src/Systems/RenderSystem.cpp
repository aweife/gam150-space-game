#include "RenderSystem.h"
#include "AEEngine.h"

void RenderSystem::Init()
{
}

void RenderSystem::Update()
{
	// Update all entities that has the components we want
	for (auto const& entity : entitiesList)
	{
		//auto const& transform = 
		//auto const& mesh =

		//AEGfxSetBlendMode(AE_GFX_BM_BLEND)

		//AEGfxSetRenderMode(AE_GFX_RM_T);

		//AEGfxSetPosition(transform.);

		//AEGfxTextureSet(NULL, 0, 0);					// No texture for object 1

		//AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);		// No tint  

		//AEGfxSetTransparency(1.0f)

		//Draw System
		// Drawing the mesh (list of triangles)
		//AEGfxMeshDraw((i.second)->_mesh, AE_GFX_MDM_TRIANGLES);
	}
}