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

		//AEGfxSetRenderMode(AE_GFX_RM_COLOR);

		//AEGfxSetPosition(transform.);

		//AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);		// No tint  

		//AEGfxTextureSet(NULL, 0, 0);					// No texture for object 1


		//Draw System
		// Drawing the mesh (list of triangles)
		//AEGfxMeshDraw((i.second)->_mesh, AE_GFX_MDM_TRIANGLES);
	}
}