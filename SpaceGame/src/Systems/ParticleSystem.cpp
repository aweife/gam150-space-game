#include "ParticleSystem.h"
#include "../ECS/Core.h"
#include "../Components/cTransform.h"
#include "../Components/cParticle.h"

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

}

void ParticleSystem::Render()
{

}

void ParticleSystem::OnComponentAdd(ENTITY entity)
{

}



