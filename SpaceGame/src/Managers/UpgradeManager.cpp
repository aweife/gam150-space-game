#include "UpgradeManager.h"
#include <unordered_map>

namespace UpgradeManager
{
	//private containers
	bool isLoaded = false;
	std::unordered_map<UpgradePackages, PlayerUpgrade_Base*> database_playerUpgrade;
	std::unordered_map<UpgradePackages, WeaponUpgradeRange_BaseRange*> database_rangeUpgrade;
	std::unordered_map<UpgradePackages, WeaponUpgradeMelee_BaseMelee*> database_meleeUpgrade;

	int upgrade1 = -1;
	int upgrade2 = -1;
	int upgrade3 = -1;

	void Init_UpgradeDatabase()
	{
		if (!isLoaded)
		{
			database_playerUpgrade.emplace(UpgradePackages::PlayerUpgrade_HpUp1, new PlayerUpgrade_HpUp1);
			database_playerUpgrade.emplace(UpgradePackages::PlayerUpgrade_LifeUp1, new PlayerUpgrade_LifeUp1);
			database_playerUpgrade.emplace(UpgradePackages::PlayerUpgrade_ShieldUp1, new PlayerUpgrade_ShieldUp1);
			database_playerUpgrade.emplace(UpgradePackages::PlayerUpgrade_ThrustAccelUp1, new PlayerUpgrade_ThrustAccelUp1);



			database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_FireRateDown1, new RangeWeaponUpgrade_FireRateDown1);
			database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_ReloadRateDown1, new RangeWeaponUpgrade_ReloadRateDown1);
			database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_AmmoUp1, new RangeWeaponUpgrade_AmmoUp1);
			database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_DamageUp1, new RangeWeaponUpgrade_DamageUp1);
			database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_SpreadDown1, new RangeWeaponUpgrade_SpreadDown1);
			database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_BulletSizeUp1, new RangeWeaponUpgrade_BulletSizeUp1);
			database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_BulletSpeedUp1, new RangeWeaponUpgrade_BulletSpeedUp1);

			database_meleeUpgrade.emplace(UpgradePackages::MeleeWeaponUpgrade_RangeUp1, new MeleeWeaponUpgrade_RangeUp1);
			database_meleeUpgrade.emplace(UpgradePackages::MeleeWeaponUpgrade_DamageUp1, new MeleeWeaponUpgrade_DamageUp1);
			//database_rangeUpgrade.emplace(UpgradePackages::Range_Pistol, new WeaponUpgrade_Pistol);
			//database_meleeUpgrade.emplace(UpgradePackages::Melee_Normal, new WeaponUpgrade_Normal);


			isLoaded = true;
		}
	}

	void PlayerUpgrade(cSpaceShip* spaceship, cHealth* health, UpgradePackages upgradePack)
	{
		PlayerUpgrade_Base* data = database_playerUpgrade[upgradePack];
		
		spaceship->_thrustDelay			+= data->Get_ThrustAcceleration();
		health->_healthMax				+= data->Get_ShieldIncrease();
		health->_shieldMax				+= data->Get_HealthIncrease();

	}

	void WeaponUpgradeRange(cRangeWeapon* rangeWeapon, UpgradePackages upgradePack)
	{
		WeaponUpgradeRange_BaseRange* data = database_rangeUpgrade[upgradePack];

			rangeWeapon->_attackCooldown	-= data->Get_FireRateDecrease();
			rangeWeapon->_reloadRate		-= data->Get_ReloadRateDecrease();
			rangeWeapon->_ammo				+= data->Get_AmmoIncrease();
			rangeWeapon->_damage			+= data->Get_DamageIncrease();
			rangeWeapon->_shootingSpread	-= data->Get_SpreadDecrease();
			rangeWeapon->_bulletSize		-= data->Get_BulletSizeIncrease();
			rangeWeapon->_bulletSpeed		+= data->Get_BulletSpeedIncrease();
	}

	void WeaponUpgradeMelee(cMeleeWeapon* meleeWeapon, UpgradePackages upgradePack)
	{
		WeaponUpgradeMelee_BaseMelee* data = database_meleeUpgrade[upgradePack];

			meleeWeapon->_meleeRange += data->Get_RangeIncrease();
			meleeWeapon->_damage += data->Get_DamageIncrease();

	}

	int RandomUpgrade()
	{
		int randomUpgradeType = rand() % NUMBER_OF_UPGRADES_TYPE + 1;
		int randomUpgrade = 0;
		bool isUnique = false;

		while (isUnique)
		{
			if (randomUpgradeType == 1) // Player Upgrade
			{
				randomUpgrade = rand() % NUMBER_OF_PLAYERPGRADES;
			}
			else if (randomUpgradeType == 2) // Range Weapon Upgrade
			{
				randomUpgrade = rand() % NUMBER_OF_RANGEWEAPONUPGRADES + NUMBER_OF_PLAYERPGRADES;
			}
			else if (randomUpgradeType == 3) // Melee Weapon Upgrade
			{
				randomUpgrade = rand() % NUMBER_OF_MELEEWEAPONUPGRADES + NUMBER_OF_RANGEWEAPONUPGRADES + NUMBER_OF_PLAYERPGRADES;
			}
		}

		return randomUpgrade;
	}

	bool CheckUnique()
	{
		if (upgrade1 == upgrade2 || upgrade1 == upgrade3
			|| upgrade2 == upgrade3)
		{
			return false;
		}
		return true;
	}

	void ClearAllUpgradeChoice()
	{
		upgrade1 = -1;
		upgrade2 = -1;
		upgrade3 = -1;
	}

	

	//void WeaponUpgradeMelee(cMeleeWeapon* meleeWeapon, UpgradePackages upgradePack, int level)
	//{
	//	WeaponUpgrade_BaseMelee* data = database_meleeUpgrade[upgradePack];

	//	switch (level)
	//	{
	//	case 1:
	//		meleeWeapon->_meleeRange		+= data->Get_U1_MeleeRange();
	//		meleeWeapon->_damage			+= data->Get_U1_Damage();
	//		break;
	//	}
	//}

	//void WeaponChange(cRangeWeapon* rangeWeapon, WeaponType weaponType, UpgradePackages upgradePack)
	//{
	//	rangeWeapon->_currWeapon = weaponType;
	//	//Reset the upgrade values
	//	WeaponUpgrade_BaseRange* data = database_rangeUpgrade[upgradePack];

	//	rangeWeapon->_fireRate				= data->Get_U0_FireRate();
	//	rangeWeapon->_reloadRate			= data->Get_U0_ReloadRate();
	//	rangeWeapon->_ammo					= data->Get_U0_Ammo();
	//	rangeWeapon->_damage				= data->Get_U0_Damage();
	//}

	void Cleanup_UpgradeDatabase()
	{
		if (isLoaded)
		{
			for (auto it = database_playerUpgrade.begin(); it != database_playerUpgrade.end(); ++it)
			{
				if (it->second != nullptr)
				{
					delete it->second;
					it->second = nullptr;
				}
			}
			database_playerUpgrade.clear();

			for (auto it = database_rangeUpgrade.begin(); it != database_rangeUpgrade.end(); ++it)
			{
				if (it->second != nullptr)
				{
					delete it->second;
					it->second = nullptr;
				}
			}
			database_rangeUpgrade.clear();

			for (auto it = database_meleeUpgrade.begin(); it != database_meleeUpgrade.end(); ++it)
			{
				if (it->second != nullptr)
				{
					delete it->second;
					it->second = nullptr;
				}
			}
			database_meleeUpgrade.clear();

			isLoaded = false;
		}
	}
}
	