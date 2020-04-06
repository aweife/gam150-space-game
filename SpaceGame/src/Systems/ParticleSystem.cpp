#include "ParticleSystem.h"
#include "../ECS/Core.h"
#include "../Components/cTransform.h"
#include "../Components/cParticle.h"
#include "../Components/cParticleEmitter.h"
#include "../Global.h"
#include "../Math/Math.h"
#include "AEEngine.h"

void ParticleSystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cParticle>());
	Core::Get().SetSystemSignature<ParticleSystem>(signature);
}

void ParticleSystem::Update()
{
	cTransform* transformComp;
	cParticle* particleComp;
	cParticleEmitter* emitterComp;

	AEVec2 cameraLastFramePostion, velocityVector, displacement;

	AEGfxGetCamPosition(&cameraLastFramePostion.x, &cameraLastFramePostion.y);

	//Temporaray Hack
	float originalDeltaTime = g_dt;
	if (g_dt > 1/60.0f)
	{
		g_dt = 1 / 60.0f;
	}

	for (auto const& particles : entitiesList)
	{
		transformComp = Core::Get().GetComponent<cTransform>(particles);
		particleComp = Core::Get().GetComponent<cParticle>(particles);
		emitterComp = Core::Get().GetComponent<cParticleEmitter>(particleComp->_emitterID);

		if (particleComp->_isAlive == false) continue;

		//Time
		particleComp->_particleData._currLifeTime += g_dt;
		if (particleComp->_particleData._currLifeTime > particleComp->_particleData._totalLifeTime)
		{
			//Killed and Sent for recycling
			particleComp->_isAlive = false;
			particleComp->_isVisible = false;
			emitterComp->_recycleParticlePool.push(particles);
			continue;
		}

		//dynamics (Movement..)
		if (particleComp->_particleData._directionOverLifetime.size() > 0)
		{
			float fixedInterval1 = particleComp->_particleData._totalLifeTime / particleComp->_particleData._directionOverLifetime.size();
			size_t currIndex1 = static_cast<size_t>(particleComp->_particleData._currLifeTime / fixedInterval1);
			AEVec2Sub(&displacement, &particleComp->_particleData._directionOverLifetime.at(currIndex1), &particleComp->_particleData._direction);
			
			float displacementTimeValue1 = ((currIndex1 + 1) * fixedInterval1) - particleComp->_particleData._currLifeTime;
			AEVec2Scale(&displacement, &displacement, g_dt / displacementTimeValue1);
			AEVec2Add(&particleComp->_particleData._direction, &particleComp->_particleData._direction, &displacement);
		}
		
		if (particleComp->_particleData._velocityOverLifetime.size() > 0 )
		{
			float fixedInterval2 = particleComp->_particleData._totalLifeTime / particleComp->_particleData._velocityOverLifetime.size();
			size_t currIndex2 = static_cast<size_t>(particleComp->_particleData._currLifeTime / fixedInterval2);
			float displacement2 = particleComp->_particleData._velocityOverLifetime.at(currIndex2) - particleComp->_particleData._velocityBase;
			
			float displacementTimeValue2 = ((currIndex2 + 1) * fixedInterval2) - particleComp->_particleData._currLifeTime;
			displacement2 *= g_dt / displacementTimeValue2;
			particleComp->_particleData._velocityBase += displacement2;
		}
		
		//Final position
		//Gravity
		AEVec2Set(&particleComp->_particleData._currGravity, particleComp->_particleData._currGravity.x + (particleComp->_particleData._gravity.x *g_dt)
			, particleComp->_particleData._currGravity.y + (particleComp->_particleData._gravity.y * g_dt ));
		//Velocity
		AEVec2Scale(&velocityVector, &particleComp->_particleData._direction, particleComp->_particleData._velocityBase);
		AEVec2Set(&velocityVector, velocityVector.x + (particleComp->_particleData._currGravity.x), velocityVector.y + (particleComp->_particleData._currGravity.y));
		AEVec2Scale(&velocityVector, &velocityVector, g_dt);
		AEVec2Add(&transformComp->_position, &transformComp->_position, &velocityVector);

		particleComp->_particleData._rotation;
		transformComp->_rotation = particleComp->_particleData._rotation;

		//Visual changes (Color, size...)
		if (particleComp->_particleData._colorOverLifetime.size() > 0)
		{
			float fixedInterval3 = particleComp->_particleData._totalLifeTime / particleComp->_particleData._colorOverLifetime.size();
			size_t currIndex3 = static_cast<size_t>(particleComp->_particleData._currLifeTime / fixedInterval3);
			float displacementTimeValue3 = ((currIndex3 + 1) * fixedInterval3) - particleComp->_particleData._currLifeTime;
			
			ColorInfo displacement3 = {(particleComp->_particleData._colorOverLifetime.at(currIndex3).r - particleComp->_particleData._currColor.r) * g_dt / displacementTimeValue3
				, (particleComp->_particleData._colorOverLifetime.at(currIndex3).g - particleComp->_particleData._currColor.g)* g_dt / displacementTimeValue3
				, (particleComp->_particleData._colorOverLifetime.at(currIndex3).b - particleComp->_particleData._currColor.b)* g_dt / displacementTimeValue3
				, (particleComp->_particleData._colorOverLifetime.at(currIndex3).a - particleComp->_particleData._currColor.a)* g_dt / displacementTimeValue3
			};
			particleComp->_particleData._currColor.r += displacement3.r;
			particleComp->_particleData._currColor.g += displacement3.g;
			particleComp->_particleData._currColor.b += displacement3.b;
			particleComp->_particleData._currColor.a += displacement3.a;

		}
		particleComp->_particleData._currColor;

		//SCALE
		if (particleComp->_particleData._scaleOverLifetime.size() > 0)
		{
			float fixedInterval = particleComp->_particleData._totalLifeTime / particleComp->_particleData._scaleOverLifetime.size();
			size_t currIndex = static_cast<size_t>(particleComp->_particleData._currLifeTime / fixedInterval);
			AEVec2Sub(&displacement, &particleComp->_particleData._scaleOverLifetime.at(currIndex), &particleComp->_particleData._scaleFactor);

			float displacementTimeValue = ((currIndex + 1) * fixedInterval) - particleComp->_particleData._currLifeTime;
			AEVec2Scale(&displacement, &displacement, g_dt / displacementTimeValue);
			AEVec2Add(&particleComp->_particleData._scaleFactor, &particleComp->_particleData._scaleFactor, &displacement);
		}
		AEVec2Set(&transformComp->_scale, particleComp->_particleData._scaleFactor.x, particleComp->_particleData._scaleFactor.y);

		//Visibillity Checks (Depends on OOB or size or alpha)
		if (abs(transformComp->_position.x - cameraLastFramePostion.x) > g_WindowWidth * 0.6f 
			|| abs(transformComp->_position.y - cameraLastFramePostion.y) > g_WindowHeight * 0.6f)
		{
			//Give 0.1f leyway
			particleComp->_isVisible = false;
		}
		else if (particleComp->_particleData._scaleFactor.x < 0.1f || particleComp->_particleData._scaleFactor.y < 0.1f)
		{
			particleComp->_isVisible = false;
		}
		else if (particleComp->_particleData._currColor.a < 0.05f)
		{
			particleComp->_isVisible = false;
		}
		particleComp->_isVisible = true;
	}

	g_dt = originalDeltaTime;
}

void ParticleSystem::RenderLayer(unsigned int layer, float parallaxOffX, float parallaxOffY)
{
	auto beginIterator	= entityLayer6.begin();
	auto endIterator	= entityLayer6.begin();
	switch (layer)
	{
		case 7:
			beginIterator	= entityLayer7.begin();
			endIterator		= entityLayer7.end();
			break;
		case 6:
			beginIterator	= entityLayer6.begin();
			endIterator		= entityLayer6.end();
			break;
		case 5:
			beginIterator	= entityLayer5.begin();
			endIterator		= entityLayer5.end();
			break;
		case 4:
			beginIterator	= entityLayer4.begin();
			endIterator		= entityLayer4.end();
			break;
		case 3:
			beginIterator	= entityLayer3.begin();
			endIterator		= entityLayer3.end();
			break;
		case 2:
			beginIterator	= entityLayer2.begin();
			endIterator		= entityLayer2.end();
			break;
		case 1:
			beginIterator	= entityLayer1.begin();
			endIterator		= entityLayer1.end();
			break;
		case 0:
			beginIterator	= entityLayer0.begin();
			endIterator		= entityLayer0.end();
			break;
	}
	cTransform* transformComp;
	cParticle* particleComp;

	for (auto particles = beginIterator; particles != endIterator; ++particles)
	{
		transformComp = Core::Get().GetComponent<cTransform>(*particles);
		particleComp = Core::Get().GetComponent<cParticle>(*particles);

		if (particleComp->_isVisible == false) continue;
		// -----------------------------------------------------------------------
		// Prepare TRANSFORM for rendering - SCALE, ROTATION, TRANSLATION
		// -----------------------------------------------------------------------
		AEMtx33 trans, rot, scale;
		// Calculate the identity matrix
		AEMtx33Identity(&trans);
		AEMtx33Identity(&rot);
		AEMtx33Identity(&scale);

		//  Compute the SCALE, ROTATION matrix from ENTITY
		AEMtx33Scale(&scale, transformComp->_scale.x, transformComp->_scale.y);
		AEMtx33Rot(&rot, transformComp->_rotation);
		//  Compute the TRANSLATION matrix after PARALLAX
		AEMtx33Trans(&trans, transformComp->_position.x + parallaxOffX, transformComp->_position.y + parallaxOffY);

		// Concatenate the 3 matrix in the correct order in the object instance's "_transform" matrix
		// Order of matrix concatenation: Translation*Rotation*Scaling
		AEMtx33Concat(&transformComp->_transform, &rot, &scale);
		AEMtx33Concat(&transformComp->_transform, &trans, &transformComp->_transform);

		// -----------------------------------------------------------------------
		// RENDERING EFFECTS
		// -----------------------------------------------------------------------
		if (particleComp->_texture == nullptr)
		{
			// Use Color
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		}
		else
		{
			// Use textures
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			// Set texture
			AEGfxTextureSet(particleComp->_texture, 0.0f, 0.0f);
		}
		
		// Set blend mode to blend so we can render transparency
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		//Transparency
		AEGfxSetTransparency(particleComp->_particleData._currColor.a);
		// No tint
		AEGfxSetTintColor(particleComp->_particleData._currColor.r, particleComp->_particleData._currColor.g
			, particleComp->_particleData._currColor.b, particleComp->_particleData._currColor.a);

		// Render at _position
		AEGfxSetTransform(transformComp->_transform.m);

		//Draw
		AEGfxMeshDraw(particleComp->_mesh, AE_GFX_MDM_TRIANGLES);
	}
}

void ParticleSystem::OnComponentAdd(ENTITY entity)
{
	//Sort the entity into different layers
	cParticle* particleComp = Core::Get().GetComponent<cParticle>(entity);
	switch (particleComp->_particleData._layer)
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
void ParticleSystem::OnComponentRemove(ENTITY entity)
{
	//Sort the entity into different layers
	cParticle* particleComp = Core::Get().GetComponent<cParticle>(entity);
	switch (particleComp->_particleData._layer)
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
	default:
		break;
	}
}



