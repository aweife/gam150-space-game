#include "ProjectileSystem.h"
#include "../ECS/Core.h"
#include "../Global.h"							//delta time
#include "../Components/cProjectile.h"

#include "../ECS/Factory.h"
/******************************************************************************/
/*!
	Global Variables
*/
/******************************************************************************/

void ProjectileSystem::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cProjectile>());
	Core::Get().SetSystemSignature<ProjectileSystem>(signature);
}

void ProjectileSystem::Update()
{
	cTransform* transform;
	cProjectile* projectile;

	for (auto const& entity : entitiesList)
	{
		projectile = Core::Get().GetComponent<cProjectile>(entity);

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