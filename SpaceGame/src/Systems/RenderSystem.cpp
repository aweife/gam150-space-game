#include "RenderSystem.h"
#include "AEEngine.h"
#include "../ECS/Core.h"
#include "../Components/cTransform.h"
#include "../Components/cSprite.h"

void RenderSystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>(), true);
	signature.set(Core::Get().GetComponentType<cSprite>(), true);
	Core::Get().SetSystemSignature<RenderSystem>(signature);
}

void RenderSystem::Update() {}

void RenderSystem::Render()
{
	cTransform* _transform;
	cSprite* sprite;
	
	float cameraX, cameraY;
	AEGfxGetCamPosition(&cameraX, &cameraY);
	// Update all entities that has the components we want
	
	for (auto const& layer : allLayer)
	{
		for (auto const& entity : *layer)
		{
			_transform = Core::Get().GetComponent<cTransform>(entity);
			sprite = Core::Get().GetComponent<cSprite>(entity);

			// Set _transform
			AEMtx33 trans, rot, _scale;
			// Calculate the identity matrix
			AEMtx33Identity(&trans);
			AEMtx33Identity(&rot);
			AEMtx33Identity(&_scale);

			// Compute the scaling matrix
			AEMtx33Scale(&_scale, _transform->_scale.x, _transform->_scale.y);

			// Compute the _rotation matrix 
			AEMtx33Rot(&rot, _transform->_rotation);

			float parallaxOffsetX = 0;
			float parallaxOffsetY = 0;
			if (sprite->_layer > 0 && sprite->_layer < 6)
			{
				//Render with parallax offset
				parallaxOffsetX = cameraX * -0.3 * sprite->_layer;
				parallaxOffsetY = cameraY * -0.3 * sprite->_layer;
			}
			

			// Compute the translation matrix
			AEMtx33Trans(&trans, _transform->_position.x + parallaxOffsetX, _transform->_position.y + parallaxOffsetY);


			// Concatenate the 3 matrix in the correct order in the object instance's "_transform" matrix
			// Order of matrix concatenation: Translation*Rotation*Scaling
			AEMtx33Concat(&_transform->_transform, &rot, &_scale);
			AEMtx33Concat(&_transform->_transform, &trans, &_transform->_transform);

			// Set blend mode to blend so we can render transparency
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);

			// Use textures
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

			// Render at _position
			AEGfxSetTransform(_transform->_transform.m);




			// Position texture
			AEGfxTextureSet(sprite->_texture, 0.0f, 0.0f);

			// No tint
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

			AEGfxSetTransparency(1.0f);

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
	cSprite* sprite = Core::Get().GetComponent<cSprite>(entity);
	if (sprite == nullptr) return;
	switch (sprite->_layer)
	{
	case 0:
		entityLayer0.erase(entity);
		break;
	case 1:
		entityLayer1.erase(entity);
		break;
	case 2:
		entityLayer2.erase(entity);
		break;
	case 3:
		entityLayer3.erase(entity);
		break;
	case 4:
		entityLayer4.erase(entity);
		break;
	case 5:
		entityLayer5.erase(entity);
		break;
	default:
		break;
	}
}