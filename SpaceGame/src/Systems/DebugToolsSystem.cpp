#include "DebugToolsSystem.h"
#include "../ECS/Core.h"
#include "../Components/cDebugTools.h"


void DebugToolsSystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cDebugTools>());
	Core::Get().SetSystemSignature<DebugToolsSystem>(signature);
}

void DebugToolsSystem::Render()
{
	for (auto const& entity : entitiesList)
	{
		cDebugTools* debugTComponent = Core::Get().GetComponent<cDebugTools>(entity);

		// -----------------------------------------------------------------------
		// Prepare TRANSFORM for rendering - SCALE, ROTATION, TRANSLATION
		// -----------------------------------------------------------------------
		AEMtx33 trans, rot, scale, transformM;
		// Calculate the identity matrix
		AEMtx33Identity(&trans);
		AEMtx33Identity(&rot);
		AEMtx33Identity(&scale);

		AEMtx33Scale(&scale, debugTComponent->_referenceScale, debugTComponent->_referenceScale);
		float rotation = atan2f(debugTComponent->_referenceRotation.y, debugTComponent->_referenceRotation.x);
		AEMtx33Rot(&rot, rotation);
		AEMtx33Trans(&trans, debugTComponent->_referencePosition.x, debugTComponent->_referencePosition.y);

		// Concatenate the 3 matrix in the correct order in the object instance's "_transform" matrix
		// Order of matrix concatenation: Translation*Rotation*Scaling
		AEMtx33Concat(&transformM, &rot, &scale);
		AEMtx33Concat(&transformM, &trans, &transformM);

		if (debugTComponent->_specifier == DEBUGTYPE::DEBUG_ARROW)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetTransform(transformM.m);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);					//White and Opaque
			AEGfxMeshDraw(debugTComponent->_mesh, AE_GFX_MDM_LINES_STRIP);
		}
		
	}
}