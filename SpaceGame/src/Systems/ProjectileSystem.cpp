#include "ProjectileSystem.h"
#include "../ECS/Core.h"
#include "../Global.h"							//delta time
#include "../Components/ComponentList.h"
#include "../Player/PlayerManager.h"

#include "../ECS/Factory.h"
#include "../Managers/AIBehaviors.h"
/******************************************************************************/
/*!
	Global Variables
*/
/******************************************************************************/

void ProjectileSystem::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cRigidBody>());
	signature.set(Core::Get().GetComponentType<cProjectile>());
	Core::Get().SetSystemSignature<ProjectileSystem>(signature);
}

void ProjectileSystem::Update()
{
	const ENTITY pid = PlayerManager::player;
	if (pid == 0)	return;				//NO ACTIVE PLAYER

	cTransform* trans;
	cRigidBody* rb;
	cProjectile* projectile;

	for (auto const& entity : entitiesList)
	{
		trans = Core::Get().GetComponent<cTransform>(entity);
		rb = Core::Get().GetComponent<cRigidBody>(entity);
		projectile = Core::Get().GetComponent<cProjectile>(entity);

		if (projectile->_homing)
			HomingTarget(Core::Get().GetComponent<cTransform>(projectile->_targetId)->_position, trans->_position, rb->_velocityVector, rb->_steeringVector, trans->_rotation);


		// Destroy projectile
		projectile->_currBulletLifeTime -= g_dt;
		if(projectile->_currBulletLifeTime <= 0)
		{
			objToDestory.insert(entity);
			projectile->_currBulletLifeTime = projectile->_bulletLifeTime;
		}
		

		//Time update
	}

	if (objToDestory.size() > 0)
	{
		for (auto const& id : objToDestory)
		{
			Core::Get().EntityDestroyed(id);
		}
		objToDestory.clear();
	}
}

void ProjectileSystem::HomingTarget(AEVec2& targetPos, AEVec2& selfPos, AEVec2& velCurr, AEVec2& steering, float& dirCurr)
{
	AEVec2 towardsTarget;
	AEVec2Sub(&towardsTarget, &targetPos, &selfPos);				//Vector towards target
	AEVec2Normalize(&towardsTarget, &towardsTarget);

	//AEVec2 currDirection;
	//AEVec2Normalize(&currDirection, &velCurr);					//Normalised bullet current direction
	//AEVec2Lerp(&velCurr, &towardsTarget, &currDirection, g_dt);	//Slowly lerp towards target direction


	////This portion is for the bullet orientation
	//AEVec2 forwardVect;
	//AEVec2Set(&forwardVect, 1, 0);
	////Facing Direction for homing bullet
	//dirCurr = AEACos(AEVec2DotProduct(&velCurr, &forwardVect));
	//towardsTarget.y < 0 ? dirCurr *= -1 : dirCurr;
	////New Velocity
	//AEVec2Scale(&velCurr, &velCurr, 10.0f);

	dirCurr = atan2f(towardsTarget.y, towardsTarget.x);
	dirCurr += PI / 2.0f;
	Steering::SeekTarget(steering, towardsTarget, 60.0f, velCurr);
}