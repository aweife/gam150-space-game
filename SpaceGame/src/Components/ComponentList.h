/**********************************************************************************
* \file			ComponentList.h
* \brief		List of components for the engine
* \author		Jun Yi,				Chong,  25% Code Contribution
*				Wei Feng,			  Ang,  25% Code Contribution
*				Jin Kiat,			Chong,  25% Code Contribution
*				Farzaana Binte,	   Roslan,  25% Code Contribution
*
*				List of Components of the engine
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

// Base Component Class
#include "Component.h"

// A collection of all headers for components in game
// Essentials
#include "cSprite.h"
#include "cTransform.h"
#include "cCamera.h"
// Physics
#include "cRigidBody.h"
#include "cCollision.h"
// AI
#include "cAI.h"
#include "cBoss.h"
// Player
#include "cSpaceShip.h"
#include "cWeapon.h"
#include "cHealth.h"
#include "cProjectile.h"
// Additional Graphics
#include "cUIElement.h"
#include "cDebugTools.h"
#include "cParticle.h"
#include "cParticleEmitter.h"
#include "cTimeline.h"

#include "cWarping.h"
#include "cScanner.h"