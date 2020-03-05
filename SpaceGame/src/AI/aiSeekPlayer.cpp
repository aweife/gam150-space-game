#include "aiState.h"
#include "../Tools/Editor.h"

void aiSeekPlayer::Run(const aiBlackBoard& blackboard, the_variant& currentState)
{
	Editor_TrackVariable("AI STATE", 1);
	static int count = 0;
	count++;
	if (count > 500)
	{
		currentState.m_Varient.emplace<aiFleePlayer>();
		count = 0;
	}
}
