#include "RenderSystem.h"								//Self Header
#include "AEEngine.h"									//Graphics Libaray and Camera
#include "../ECS/Core.h"								//Game Engine
#include "../Components/cTransform.h"					//Required Component to manage 
#include "../Components/cSprite.h"						
#include "../Global.h"									//Window Width and Height for parallax

void RenderSystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cSprite>());
	Core::Get().SetSystemSignature<RenderSystem>(signature);
}

void RenderSystem::Render() 
{
	//Reference Components when looping through ENTITY
	cTransform* _transform;
	cSprite* sprite;

	//Camera position
	float cameraX, cameraY;		
	AEGfxGetCamPosition(&cameraX, &cameraY);

	// -----------------------------------------------------------------------
	// Update all entities that has the components we want
	// -----------------------------------------------------------------------
	for (auto const& layer : allLayer)
	{
		for (auto const& entity : *layer)
		{
			_transform = Core::Get().GetComponent<cTransform>(entity);
			sprite = Core::Get().GetComponent<cSprite>(entity);

			// -----------------------------------------------------------------------
			// Prepare TRANSFORM for rendering - SCALE, ROTATION, TRANSLATION
			// -----------------------------------------------------------------------
			AEMtx33 trans, rot, _scale;
			// Calculate the identity matrix
			AEMtx33Identity(&trans);
			AEMtx33Identity(&rot);
			AEMtx33Identity(&_scale);

			//  Compute the SCALE, ROTATION matrix from ENTITY
			AEMtx33Scale(&_scale, _transform->_scale.x, _transform->_scale.y);
			AEMtx33Rot(&rot, _transform->_rotation);

			// -----------------------------------------------------------------------
			//  Parallax Background calculation...displace layers based on camera from origin
			// -----------------------------------------------------------------------
			float parallaxOffsetX = 0.0f;
			float parallaxOffsetY = 0.0f;
			if (sprite->_layer > 2 && sprite->_layer < 6)				//BACKGROUND <--
			{
				//Render with parallax offset
				parallaxOffsetX = cameraX * -0.1f * sprite->_layer;
				parallaxOffsetY = cameraY * -0.1f * sprite->_layer;
			}
			if (sprite->_layer == 1)									//FOREGROUND -->
			{
				//Render with parallax offset
				parallaxOffsetX = cameraX * 0.1f * sprite->_layer;
				parallaxOffsetY = cameraY * 0.1f * sprite->_layer;
			}

			//  Compute the TRANSLATION matrix after PARALLAX
			AEMtx33Trans(&trans, _transform->_position.x + parallaxOffsetX, _transform->_position.y + parallaxOffsetY);

			// Concatenate the 3 matrix in the correct order in the object instance's "_transform" matrix
			// Order of matrix concatenation: Translation*Rotation*Scaling
			AEMtx33Concat(&_transform->_transform, &rot, &_scale);
			AEMtx33Concat(&_transform->_transform, &trans, &_transform->_transform);

			// -----------------------------------------------------------------------
			// RENDERING EFFECTS
			// -----------------------------------------------------------------------
			// Use textures
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			// Set texture
			AEGfxTextureSet(sprite->_texture, 0.0f, 0.0f);

			// Set blend mode to blend so we can render transparency
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			//Transparency
			AEGfxSetTransparency(1.0f);
			// No tint
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

			// Render at _position
			AEGfxSetTransform(_transform->_transform.m);

			//Draw
			AEGfxMeshDraw(sprite->_mesh, AE_GFX_MDM_TRIANGLES);
		}
	}
}

void RenderSystem::OnComponentAdd(ENTITY entity)
{
	//Sort the entity into different layers
	cSprite* sprite = Core::Get().GetComponent<cSprite>(entity);
	switch (sprite->_layer)
	{
	case 0:
		entityLayer0.insert(entity);
		break;
	case 1:
		entityLayer1.insert(entity);
		break;
	case 2:
		entityLayer2.insert(entity);
		break;
	case 3:
		entityLayer3.insert(entity);
		break;
	case 4:
		entityLayer4.insert(entity);
		break;
	case 5:
		entityLayer5.insert(entity);
		break;
	case 6:
		entityLayer6.insert(entity);
		break;
	default:
		break;
	}

}
void RenderSystem::OnComponentRemove(ENTITY entity)
{
	entityLayer0.erase(entity);
	entityLayer1.erase(entity);
	entityLayer2.erase(entity);
	entityLayer3.erase(entity);
	entityLayer4.erase(entity);
	entityLayer5.erase(entity);
	entityLayer6.erase(entity);

}
