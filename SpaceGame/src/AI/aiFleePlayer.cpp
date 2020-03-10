#include "aiState.h"
#include "../Tools/Editor.h"

void aiFleePlayer::Run( const aiBlackBoard&, the_variant& Varient )
{
	Editor_TrackVariable("AI STATE", 2);
	static int count = 0;
	count++;
	if (count > 500)
	{
		Varient.m_Varient.emplace<aiChase>();
		count = 0;
	}
}
