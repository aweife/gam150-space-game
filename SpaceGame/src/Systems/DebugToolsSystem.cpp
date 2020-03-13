#include "DebugToolsSystem.h"
#include "../ECS/Core.h"
#include "../Components/cDebugTools.h"
#include "../ECS/Factory.h"
#include "../Systems/CollisionSystem.h"					//Get List of all rigidbody in scene
#include <memory>										//shared pointer
#include "../Tools/Console.h"		

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

		if (debugTComponent->_specifier != DEBUGTYPE::DEBUG_LINE)
		{
			AEMtx33Scale(&scale, debugTComponent->_referenceScaleX, debugTComponent->_referenceScaleY);
			float rotation;
			if (debugTComponent->_referenceAngle != 0)
			{
				rotation = debugTComponent->_referenceAngle;
			}
			else
			{
				rotation = atan2f(debugTComponent->_referenceRotation.y, debugTComponent->_referenceRotation.x);
			}
			AEMtx33Rot(&rot, rotation);
			AEMtx33Trans(&trans, debugTComponent->_referencePosition.x, debugTComponent->_referencePosition.y);
		}
		else
		{
			//Distance between 2 anchor points
			AEMtx33Scale(&scale, AEVec2Distance(&debugTComponent->_referenceEndPosition, &debugTComponent->_referencePosition), 1); 
			AEVec2 anchorVector;
			//Vector between 2 anchor points
			AEVec2Sub(&anchorVector, &debugTComponent->_referenceEndPosition, &debugTComponent->_referencePosition);
			float rotation = atan2f(anchorVector.y, anchorVector.x);
			AEMtx33Rot(&rot, rotation);
			AEMtx33Trans(&trans, debugTComponent->_referencePosition.x, debugTComponent->_referencePosition.y);
		}

		// Concatenate the 3 matrix in the correct order in the object instance's "_transform" matrix
		// Order of matrix concatenation: Translation*Rotation*Scaling
		AEMtx33Concat(&transformM, &rot, &scale);
		AEMtx33Concat(&transformM, &trans, &transformM);

		if (debugTComponent->_specifier == DEBUGTYPE::DEBUG_ARROW || debugTComponent->_specifier == DEBUGTYPE::DEBUG_LINE)
		{
			if (g_BBShowMode)
			{
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				AEGfxSetTransform(transformM.m);
				AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);					//White and Opaque
				AEGfxMeshDraw(debugTComponent->_mesh, AE_GFX_MDM_LINES_STRIP);
			}
		}
		else if (debugTComponent->_specifier == DEBUGTYPE::DEBUG_SQUARE)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetTransform(transformM.m);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 0.5f);					//White and Opaque
			AEGfxMeshDraw(debugTComponent->_mesh, AE_GFX_MDM_LINES_STRIP);
		}

		
	}
}

void ShowAll_BoundingBoxOutline()
{
	std::shared_ptr<DebugToolsSystem> 
		debugSystemInstance(std::static_pointer_cast<DebugToolsSystem>(Core::Get().GetSystem<DebugToolsSystem>()));

	for (auto const& entites : Core::Get().GetSystem<CollisionSystem>()->entitiesList)
	{
		debugSystemInstance->meshOutlineList.insert(Factory::DebugBoundingBox_Rigidbody(entites));
	}
	Console_Cout("Debug Bounding Box Created = ", static_cast<int>(debugSystemInstance->meshOutlineList.size()));
}

void RemoveAll_BoundingBoxOutline()
{
	std::shared_ptr<DebugToolsSystem>
		debugSystemInstance(std::static_pointer_cast<DebugToolsSystem>(Core::Get().GetSystem<DebugToolsSystem>()));
	

	for (auto const& entites : debugSystemInstance->meshOutlineList)
	{
		Core::Get().EntityDestroyed(entites);
	}

	debugSystemInstance->meshOutlineList.clear();
}
