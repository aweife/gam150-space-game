#include "UpgradeManager.h"
#include <unordered_map>

namespace UpgradeManager
{
	//private containers
	bool isLoaded = false;
	std::unordered_map<UpgradePackages, PlayerUpgrade_Base*> database_playerUpgrade;
	std::unordered_map<UpgradePackages, WeaponUpgrade_BaseRange*> database_rangeUpgrade;
	std::unordered_map<UpgradePackages, WeaponUpgrade_BaseMelee*> database_meleeUpgrade;

	void Init_UpgradeDatabase()
	{
		if (!isLoaded)
		{
			database_playerUpgrade.emplace(UpgradePackages::Player_V1, new PlayerUpgrade_V1);
			database_rangeUpgrade.emplace(UpgradePackages::Range_Pistol, new WeaponUpgrade_Pistol);
			database_meleeUpgrade.emplace(UpgradePackages::Melee_Normal, new WeaponUpgrade_Normal);
			isLoaded = true;
		}
	}

	void PlayerUpgrade(cSpaceShip* spaceship, cHealth* health, UpgradePackages upgradePack, int level)
	{
		PlayerUpgrade_Base* data = database_playerUpgrade[upgradePack];
		switch (level)
		{
			case 1:
				spaceship->_thrustDelay		+= data->Get_U1_ThrustDelay();
				spaceship->_lives			+= data->Get_U1_LifeIncrease();
				health->_healthMax			+= data->Get_U1_HealthIncrease();
				health->_shieldMax			+= data->Get_U1_ShieldIncrease();
				break;
			case 2:
				spaceship->_thrustDelay		+= data->Get_U2_ThrustDelay();
				spaceship->_lives			+= data->Get_U2_LifeIncrease();
				health->_healthMax			+= data->Get_U2_HealthIncrease();
				health->_shieldMax			+= data->Get_U2_ShieldIncrease();
				break;
		}
		
	}

	void WeaponUpgradeRange(cRangeWeapon* rangeWeapon, UpgradePackages upgradePack, int level)
	{
		WeaponUpgrade_BaseRange* data = database_rangeUpgrade[upgradePack];
		switch (level)
		{
		case 1:
			rangeWeapon->_fireCooldownTimer			+= data->Get_U1_FireRate();
			rangeWeapon->_reloadRate		+= data->Get_U1_ReloadRate();
			rangeWeapon->_ammo				+= data->Get_U1_Ammo();
			rangeWeapon->_damage			+= data->Get_U1_Damage();
			break;
		case 2:
			rangeWeapon->_fireCooldownTimer			+= data->Get_U2_FireRate();
			rangeWeapon->_reloadRate		+= data->Get_U2_ReloadRate();
			rangeWeapon->_ammo				+= data->Get_U2_Ammo();
			rangeWeapon->_damage			+= data->Get_U2_Damage();
			break;
		}
	}

	void WeaponUpgradeMelee(cMeleeWeapon* meleeWeapon, UpgradePackages upgradePack, int level)
	{
		WeaponUpgrade_BaseMelee* data = database_meleeUpgrade[upgradePack];

		switch (level)
		{
		case 1:
			meleeWeapon->_meleeRange		+= data->Get_U1_MeleeRange();
			meleeWeapon->_damage			+= data->Get_U1_Damage();
			break;
		}
	}

	void WeaponChange(cRangeWeapon* rangeWeapon, WeaponType weaponType, UpgradePackages upgradePack)
	{
		rangeWeapon->_currWeapon = weaponType;
		//Reset the upgrade values
		WeaponUpgrade_BaseRange* data = database_rangeUpgrade[upgradePack];

		rangeWeapon->_fireCooldownTimer				= data->Get_U0_FireRate();
		rangeWeapon->_reloadRate			= data->Get_U0_ReloadRate();
		rangeWeapon->_ammo					= data->Get_U0_Ammo();
		rangeWeapon->_damage				= data->Get_U0_Damage();
	}

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
	