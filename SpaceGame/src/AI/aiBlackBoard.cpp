#include "aiBlackBoard.h"

aiBlackBoard::aiBlackBoard():
	positionUpdateTimer{0.0f},

	baseAttackRange{ 350.0f },
	baseDetectRange{450.0f},
	baseMaxSpeed{ 80.0f },
	baseAcceleration{ 2.0f },
	baseRotationSpeed{ 5.0f },

	wanderAngle{ 0.0f }
{}
