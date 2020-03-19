#include "aiBlackBoard.h"

aiBlackBoard::aiBlackBoard():
	positionUpdateTimer{0.0f},
	attackRange{ 350.0f },
	maxSpeed{ 80.0f },
	acceleration{ 2.0f },
	rotationSpeed{ 10.0f },
	wanderAngle{ 0.0f }
{}
