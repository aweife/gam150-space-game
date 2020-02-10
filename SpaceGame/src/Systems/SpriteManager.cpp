///*********************************************************************************
//* \file			SpriteManager.cpp
//* \author			Chong Jun Yi, Ang Wei Feng
//* \version		1.1
//* \date			1/02/2019
//* \par			Systems
//* \note			Course: GAM150
//* \brief		Manager for 2D sprite components
//				- Render the sprites on screen
//
//* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
//				or disclosure of this file or its contents without the prior
//				written consent of DigiPen Institute of Technology is prohibited.
//**********************************************************************************/
#include "SpriteManager.h"
#include "AEEngine.h"
#include "../Global_ECS.h"
#include "../Components/TransformComponent.h"


SpriteManager::SpriteManager()
{
	Init();
}

void SpriteManager::Init()
{
	//Set system signature to indicate what components it will be managing
	_systemSignature.set(ID_SpriteComponent);

	//Assign component storage pointer
	spriteComponentList = ComponentManager::GetInstance().GetComponentStorage<SpriteComponent>();
}

void SpriteManager::Update()
{
	for (auto &i: spriteComponentList->componentMap)
	{
		/************************************************************/
		/*Rendering must be first, MeshDraw last
		/*The res can be in any order
		/************************************************************/
		//Put this into a rendering system
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		//Rendering system -- but uses transform component

		TransformComponent* trans = ComponentManager::GetInstance().GetComponent<TransformComponent>(i.first);


		AEGfxSetPosition(trans->position.x, trans->position.y);						// Set position for object 1 

		//These can remain in sprite manager
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);		// No tint  
		AEGfxTextureSet(NULL, 0, 0);					// No texture for object 1

		
		//Draw System
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw((i.second)->_mesh, AE_GFX_MDM_TRIANGLES);
		
	}
	
	
}


