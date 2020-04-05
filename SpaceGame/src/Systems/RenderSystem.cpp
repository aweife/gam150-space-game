#include "RenderSystem.h"								//Self Header
#include "AEEngine.h"									//Graphics Libaray and Camera
#include "../ECS/Core.h"								//Game Engine
#include "../Components/cTransform.h"					//Required Component to manage 
#include "../Components/cSprite.h"						
#include "../Global.h"									//Window Width and Height for parallax
#include "ParticleSystem.h"

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
	cTransform* transform;
	cSprite* sprite;

	//Camera position
	float cameraX, cameraY;		
	AEGfxGetCamPosition(&cameraX, &cameraY);
	float parallaxOffsetX = 0.0f;
	float parallaxOffsetY = 0.0f;

	//Update particle system based on layers after finished 
	std::shared_ptr<ParticleSystem> particleSystemInstance (std::static_pointer_cast<ParticleSystem>(Core::Get().GetSystem<ParticleSystem>()));
	unsigned int currentLayer = 7;

	// -----------------------------------------------------------------------
	// Update all entities that has the components we want
	// -----------------------------------------------------------------------
	for (auto const& layer : allLayer)
	{
		for (auto const& entity : *layer)
		{
			transform = Core::Get().GetComponent<cTransform>(entity);
			sprite = Core::Get().GetComponent<cSprite>(entity);

			// -----------------------------------------------------------------------
			// Prepare TRANSFORM for rendering - SCALE, ROTATION, TRANSLATION
			// -----------------------------------------------------------------------
			AEMtx33 trans, rot, scale;
			// Calculate the identity matrix
			AEMtx33Identity(&trans);
			AEMtx33Identity(&rot);
			AEMtx33Identity(&scale);

			//  Compute the SCALE, ROTATION matrix from ENTITY
			AEMtx33Scale(&scale, transform->_scale.x, transform->_scale.y);
			AEMtx33Rot(&rot, transform->_rotation);

			// -----------------------------------------------------------------------
			//  Parallax Background calculation...displace layers based on camera from origin
			// -----------------------------------------------------------------------
			parallaxOffsetX = 0.0f;
			parallaxOffsetY = 0.0f;
			if (sprite->_layer >= 5 && sprite->_layer <= 6)					//BACKGROUND <--
			{
				//Render with parallax offset
				parallaxOffsetX = cameraX * -0.001f * sprite->_layer;
				parallaxOffsetY = cameraY * -0.001f * sprite->_layer;
			}
			else if (sprite->_layer >= 3 && sprite->_layer <= 4)			//BACKGROUND <--
			{
				//Render with parallax offset
				parallaxOffsetX = cameraX * -0.05f * sprite->_layer;
				parallaxOffsetY = cameraY * -0.05f * sprite->_layer;
			}
			else if (sprite->_layer == 1)									//FOREGROUND -->
			{
				//Render with parallax offset
				parallaxOffsetX = cameraX * 0.1f * sprite->_layer;
				parallaxOffsetY = cameraY * 0.1f * sprite->_layer;
			}
			else if (sprite->_layer == 0 || sprite->_layer == 7)			//UI Layer should remain relative to screen
			{
				parallaxOffsetX = cameraX;
				parallaxOffsetY = cameraY;
			}

			//  Compute the TRANSLATION matrix after PARALLAX
			AEMtx33Trans(&trans, transform->_position.x + parallaxOffsetX, transform->_position.y + parallaxOffsetY);

			// Concatenate the 3 matrix in the correct order in the object instance's "_transform" matrix
			// Order of matrix concatenation: Translation*Rotation*Scaling
			AEMtx33Concat(&transform->_transform, &rot, &scale);
			AEMtx33Concat(&transform->_transform, &trans, &transform->_transform);

			// -----------------------------------------------------------------------
			// RENDERING EFFECTS
			// -----------------------------------------------------------------------
			if (sprite->_mode == SPRITE_RM::RM_SPRITE)
			{
				// Use textures
				AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

				// Set texture
				AEGfxTextureSet(sprite->_texture, sprite->_UVOffset.x, sprite->_UVOffset.y);

				// Set blend mode to blend so we can render transparency
				AEGfxSetBlendMode(sprite->_blend);
				//Transparency
				AEGfxSetTransparency(1.0f);
				// No tint
				AEGfxSetTintColor(sprite->_colorTint.r, sprite->_colorTint.g, sprite->_colorTint.b, sprite->_colorTint.a);
				AEGfxSetBlendColor(sprite->_colorBlend.r, sprite->_colorBlend.g, sprite->_colorBlend.b, sprite->_colorBlend.a);
				// Render at _position
				AEGfxSetTransform(transform->_transform.m);

				//Draw
				AEGfxMeshDraw(sprite->_mesh, AE_GFX_MDM_TRIANGLES);
			}
			else if (sprite->_mode == SPRITE_RM::RM_COLOR)
			{
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				AEGfxSetBlendMode(sprite->_blend);
				AEGfxSetTransparency(1.0f);
				AEGfxSetTintColor(sprite->_colorTint.r, sprite->_colorTint.g, sprite->_colorTint.b, sprite->_colorTint.a);
				AEGfxSetBlendColor(sprite->_colorBlend.r, sprite->_colorBlend.g, sprite->_colorBlend.b, sprite->_colorBlend.a);
				AEGfxSetTransform(transform->_transform.m);
				AEGfxMeshDraw(sprite->_mesh, AE_GFX_MDM_TRIANGLES);
			}
			
		}
		particleSystemInstance->RenderLayer(currentLayer, parallaxOffsetX, parallaxOffsetY);
		--currentLayer;
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
	case 7:
		entityLayer7.insert(entity);
		break;
	default:
		break;
	}

}
void RenderSystem::OnComponentRemove(ENTITY entity)
{
	cSprite* sprite = Core::Get().GetComponent<cSprite>(entity);
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
	case 6:
		entityLayer6.erase(entity);
		break;
	case 7:
		entityLayer7.erase(entity);
		break;
	default:
		break;
	}
	
	/*entityLayer0.erase(entity);
	entityLayer1.erase(entity);
	entityLayer2.erase(entity);
	entityLayer3.erase(entity);
	entityLayer4.erase(entity);
	entityLayer5.erase(entity);
	entityLayer6.erase(entity);
	entityLayer7.erase(entity); */

}

namespace RenderingTricks
{
	// Step based
	void LightSpeedEffectOut(ENTITY target, float elapsedTime, int counter, 
		float increment, float alphaDecrement, float degree)
	{
		cTransform* transform = Core::Get().GetComponent<cTransform>(target);
		cSprite* sprite = Core::Get().GetComponent<cSprite>(target);
		float angle = AEDegToRad(degree);
		
		//First frame
		if (elapsedTime <= g_dt && counter == 0)
		{
			transform->_position.x -= AECos(angle) * increment;
			transform->_position.y += AESin(angle) * increment;		//0, up
			if (sprite)
			{
				sprite->_colorTint.a -= alphaDecrement;
			}
			
		}
		else
		{
			int step = counter % 2;		//0 or 1;
			if (step)	// 1 or odd, down
			{
				transform->_position.x -= AECos(angle) * 2 * increment * ((counter / 2) + 1);
				transform->_position.y -= AESin(angle) * 2 * increment * ((counter / 2) + 1);
				if (sprite)
				{
					sprite->_colorTint.a -= alphaDecrement;
				}
			}
			else		// 0 or even, up
			{
				// Centralised first
				transform->_position.x += AECos(angle) * increment * (counter / 2);
				transform->_position.y += AESin(angle) * increment * (counter / 2);
				transform->_position.x += AECos(angle) * increment * ((counter / 2) + 1);
				transform->_position.y += AESin(angle) * increment * ((counter / 2) + 1);
				if (sprite)
				{
					sprite->_colorTint.a -= alphaDecrement;
				}
					
			}
		}
	}

	//Timebased
	void LightSpeedEffectIn(ENTITY target, float elapsedTime, float totalTime, float timeOffset,int counter,
		float maxRangeX, float maxRangeY, float desiredX, float desiredY, float alphaIncrement, float degree)
	{
		cTransform* transform = Core::Get().GetComponent<cTransform>(target);
		cSprite* sprite = Core::Get().GetComponent<cSprite>(target);
		float angle = AEDegToRad(degree);

		//First frame
		if (elapsedTime <= g_dt && counter == 0)
		{
			//Up
			transform->_position.x = desiredX + (AECos(angle) * maxRangeX);
			transform->_position.y = desiredY + (AESin(angle) * maxRangeY);		//0, up
			if (sprite)
			{
				sprite->_colorTint.a += alphaIncrement;
			}
		}
		else
		{
			int step = counter % 2;		//0 or 1;
			// +g_dt*step to retrieve previous frame distance
			//time offset used to achieve centralised position faster
			float timePercentage = (totalTime - elapsedTime + (g_dt * step) - timeOffset)/totalTime;
			timePercentage = (timePercentage < 0.0f ? 0.0f : timePercentage);
			if (step)	// 1 or odd, down
			{
				transform->_position.x = desiredX - (AECos(angle) * (maxRangeX * timePercentage));
				transform->_position.y = desiredY - (AESin(angle) * (maxRangeY * timePercentage));
				if (sprite)
				{
					sprite->_colorTint.a += alphaIncrement;
				}
			}
			else		// 0 or even, up
			{
				// Centralised first
				transform->_position.x = desiredX + (AECos(angle) * (maxRangeX * timePercentage));
				transform->_position.y = desiredY + (AESin(angle) * (maxRangeY * timePercentage));
				if (sprite)
				{
					sprite->_colorTint.a += alphaIncrement;
				}
			}
		}
	}
}
