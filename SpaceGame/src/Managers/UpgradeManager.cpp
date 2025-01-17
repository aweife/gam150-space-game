/**********************************************************************************
* \file			UpgradeManager.cpp
* \brief		Stores all upgrade values for weapon
* \author		Jin Kiat,		Chong,		100% Code Contribution
*
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "UpgradeManager.h"
#include <unordered_map>
#include <array>
#include "../Player/PlayerManager.h"
#include "../Tools/Console.h"

namespace UpgradeManager
{
	//private containers
	bool isLoaded = false;
	std::unordered_map<UpgradePackages, PlayerUpgrade_Base*> database_playerUpgrade;
	std::unordered_map<UpgradePackages, WeaponUpgradeRange_BaseRange*> database_rangeUpgrade;
	std::unordered_map<UpgradePackages, WeaponUpgradeMelee_BaseMelee*> database_meleeUpgrade;
	std::array<const char*, 20> textureNames;
	std::array<const char*, 20> descriptionNames;

	int upgrade1 = -1;
	int upgrade2 = -1;
	int upgrade3 = -1;
	UpgradePackages upgrade1Pack = UpgradePackages::NONE;
	UpgradePackages upgrade2Pack = UpgradePackages::NONE;
	UpgradePackages upgrade3Pack = UpgradePackages::NONE;

	void Init_UpgradeDatabase()
	{
		if (!isLoaded)
		{
			//3
			database_playerUpgrade.emplace(UpgradePackages::PlayerUpgrade_HpUp1, new PlayerUpgrade_HpUp1);
			textureNames[0] = "Upgrade_Health";
			descriptionNames[0] = "Health Up";
			//database_playerUpgrade.emplace(UpgradePackages::PlayerUpgrade_LifeUp1, new PlayerUpgrade_LifeUp1);
			//textureNames[1] = "PlayerUpgrade_LifeUp1";
			//textureNames[1] = "Upgrade_1";
			/*descriptionNames[1] = "Life Up";*/
			database_playerUpgrade.emplace(UpgradePackages::PlayerUpgrade_ShieldUp1, new PlayerUpgrade_ShieldUp1);
			textureNames[1] = "Upgrade_Shield";
			descriptionNames[1] = "Shield Up";
			database_playerUpgrade.emplace(UpgradePackages::PlayerUpgrade_ThrustAccelUp1, new PlayerUpgrade_ThrustAccelUp1);
			textureNames[2] = "Upgrade_Thruster";
			descriptionNames[2] = "Accel Up";

			//1
			//database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_FireRateDown1, new RangeWeaponUpgrade_FireRateDown1);
			//textureNames[4] = "RangeWeaponUpgrade_FireRateDown1";
			//textureNames[4] = "Upgrade_1";
			//descriptionNames[4] = "FireRate Up";
			//database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_ReloadRateDown1, new RangeWeaponUpgrade_ReloadRateDown1);
			//textureNames[5] = "RangeWeaponUpgrade_ReloadRateDown1";
			//textureNames[5] = "Upgrade_1";
			//descriptionNames[5] = "Reload Faster";
			//database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_AmmoUp1, new RangeWeaponUpgrade_AmmoUp1);
			//textureNames[6] = "RangeWeaponUpgrade_AmmoUp1";
			//textureNames[6] = "Upgrade_1";
			//descriptionNames[6] = "Ammo Up";
			database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_DamageUp1, new RangeWeaponUpgrade_DamageUp1);
			textureNames[3] = "Upgrade_Damage";
			descriptionNames[3] = "Damage Up";
			//database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_SpreadDown1, new RangeWeaponUpgrade_SpreadDown1);
			//textureNames[8] = "RangeWeaponUpgrade_SpreadDown1";
			//textureNames[8] = "Upgrade_1";
			//descriptionNames[8] = "Spread Down";
			//database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_BulletSizeUp1, new RangeWeaponUpgrade_BulletSizeUp1);
			//textureNames[9] = "RangeWeaponUpgrade_BulletSizeUp1";
			//textureNames[9] = "Upgrade_1";
			//descriptionNames[9] = "Bullet Size Up";
			//database_rangeUpgrade.emplace(UpgradePackages::RangeWeaponUpgrade_BulletSpeedUp1, new RangeWeaponUpgrade_BulletSpeedUp1);
			//textureNames[10] = "RangeWeaponUpgrade_BulletSpeedUp1";
			//textureNames[10] = "Upgrade_1";
			//descriptionNames[10] = "Bullet Speed Up";

			//1
			//database_meleeUpgrade.emplace(UpgradePackages::MeleeWeaponUpgrade_RangeUp1, new MeleeWeaponUpgrade_RangeUp1);
			//textureNames[11] = "MeleeWeaponUpgrade_RangeUp1";
			//textureNames[11] = "Upgrade_1";
			//descriptionNames[11] = "Melee Range Up";
			database_meleeUpgrade.emplace(UpgradePackages::MeleeWeaponUpgrade_DamageUp1, new MeleeWeaponUpgrade_DamageUp1);
			textureNames[4] = "MeleeWeaponUpgrade_DamageUp1";
			textureNames[4] = "Upgrade_1";
			descriptionNames[4] = "Melee Damage Up";

			isLoaded = true;
		}
	}

	const char* GetUpgradeImage(int i)
	{
		return textureNames[i];
	}

	const char* GetUpgradeDescript(int i)
	{
		return descriptionNames[i];
	}

	void PlayerUpgrade(cSpaceShip* spaceship, cHealth* health, UpgradePackages upgradePack)
	{
		PlayerUpgrade_Base* data = database_playerUpgrade[upgradePack];
		if (!data)	return;
		Console_Cout("Player Upgrade");
		spaceship->_thrustDelay			+= data->Get_ThrustAcceleration();
		health->_healthMax				+= data->Get_ShieldIncrease();
		health->_shieldMax				+= data->Get_HealthIncrease();

	}

	void WeaponUpgradeRange(cRangeWeapon* rangeWeapon, UpgradePackages upgradePack)
	{
		WeaponUpgradeRange_BaseRange* data = database_rangeUpgrade[upgradePack];
		Console_Cout("Range Upgrade");
		if (!data)return;
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
		Console_Cout("Melee Upgrade");
		if (!data) return;
		meleeWeapon->_meleeRange += data->Get_RangeIncrease();
		meleeWeapon->_damage += data->Get_DamageIncrease();

	}

	void ApplyUpgrade(int upgradeIndex)
	{
		if (upgradeIndex < 3)
		{
			PlayerUpgrade(&PlayerManager::playerSpaceshipProgression, &PlayerManager::playerHealthProgression
				, upgrade1Pack);
		}
		else if (upgradeIndex < 4)
		{
			WeaponUpgradeRange(&PlayerManager::playerRangeProgression, upgrade2Pack);
		}
		else if (upgradeIndex < 5)
		{
			WeaponUpgradeMelee(&PlayerManager::playerMeleeProgression, upgrade3Pack);
		}
	}

	int RandomUpgrade()
	{
		int randomUpgradeType = rand() % NUMBER_OF_UPGRADES_TYPE + 1;
		int randomUpgrade = 0;

		if (upgrade3 != -1) {
			AE_ASSERT(upgrade3 == -1 && "ALL UPGRADES ARE FULL");
			return -1;				//all upgrades full
		}
		do
		{
			if (randomUpgradeType == 1) // Player Upgrade
			{
				randomUpgrade = rand() % NUMBER_OF_PLAYERPGRADES;
			}
			else if (randomUpgradeType == 2) // Range Weapon Upgrade
			{
				randomUpgrade = (rand() % NUMBER_OF_RANGEWEAPONUPGRADES - 1) + NUMBER_OF_PLAYERPGRADES;
			}
			else if (randomUpgradeType == 3) // Melee Weapon Upgrade
			{
				randomUpgrade = (rand() % NUMBER_OF_MELEEWEAPONUPGRADES - 1) + NUMBER_OF_RANGEWEAPONUPGRADES + NUMBER_OF_PLAYERPGRADES;
			}
		} while (!CheckUnique(randomUpgrade));
		AddActiveUpgrade(randomUpgrade);

		return randomUpgrade;
	}

	bool CheckUnique(int randomUpgrade)
	{
		//Too Few to randomise
		//if (upgrade1 == randomUpgrade /*|| upgrade2 == randomUpgrade
		//	|| upgrade3 == randomUpgrade*/)
		//{
		//	return false;			//NOT UNIQUE
		//}
		return true;				//UNIQUE
	}

	void AddActiveUpgrade(int randomUpgrade)
	{
		if (upgrade1 == -1)
		{
			upgrade1 = randomUpgrade;
			
			const UpgradePackages enumValue = static_cast<UpgradePackages>(randomUpgrade);
			auto iterator = database_playerUpgrade.find(enumValue);
			auto iterator2 = database_rangeUpgrade.find(enumValue);
			auto iterator3 = database_meleeUpgrade.find(enumValue);
			if (iterator != database_playerUpgrade.end())
			{
				//found
				upgrade1Pack = (*iterator).first;
			}
			else if (iterator2 != database_rangeUpgrade.end())
			{
				//found
				upgrade1Pack = (*iterator2).first;
			}
			else if (iterator3 != database_meleeUpgrade.end())
			{
				//found
				upgrade1Pack = (*iterator3).first;
			}
			
		}
		else if (upgrade2 == -1)
		{
			upgrade2 = randomUpgrade;
			const UpgradePackages enumValue = static_cast<UpgradePackages>(randomUpgrade);
			auto iterator = database_playerUpgrade.find(enumValue);
			auto iterator2 = database_rangeUpgrade.find(enumValue);
			auto iterator3 = database_meleeUpgrade.find(enumValue);
			if (iterator != database_playerUpgrade.end())
			{
				//found
				upgrade2Pack = (*iterator).first;
			}
			else if (iterator2 != database_rangeUpgrade.end())
			{
				//found
				upgrade2Pack = (*iterator2).first;
			}
			else if (iterator3 != database_meleeUpgrade.end())
			{
				//found
				upgrade2Pack = (*iterator3).first;
			}
		}
		else if (upgrade3 == -1)
		{
			upgrade3 = randomUpgrade;
			const UpgradePackages enumValue = static_cast<UpgradePackages>(randomUpgrade);
			auto iterator = database_playerUpgrade.find(enumValue);
			auto iterator2 = database_rangeUpgrade.find(enumValue);
			auto iterator3 = database_meleeUpgrade.find(enumValue);
			if (iterator != database_playerUpgrade.end())
			{
				//found
				upgrade3Pack = (*iterator).first;
			}
			else if (iterator2 != database_rangeUpgrade.end())
			{
				//found
				upgrade3Pack = (*iterator2).first;
			}
			else if (iterator3 != database_meleeUpgrade.end())
			{
				//found
				upgrade3Pack = (*iterator3).first;
			}
		}
	}
	void ClearAllUpgradeChoice()
	{
		upgrade1 = -1;
		upgrade2 = -1;
		upgrade3 = -1;
		upgrade1Pack = UpgradePackages::NONE;
		upgrade2Pack = UpgradePackages::NONE;
		upgrade3Pack = UpgradePackages::NONE;
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
	