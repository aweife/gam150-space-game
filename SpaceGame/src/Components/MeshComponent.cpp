#include "MeshComponent.h"


MeshComponent::MeshComponent()
{
	_name = "MeshComponent";
	_category = SYS_GRAPHICS;
	_bitfieldIndex = 1;				//Temporary
}

void MeshComponent::InitComponent()
{
	GenerateMesh_Tri();
}

void MeshComponent::GenerateMesh_Tri()
{
	AEGfxMeshStart();

	// 1 triangle at a time
	// x, y, color, texu, texv
	AEGfxTriAdd(
		-25.5f, -25.5f, 0xffff0000, 0.0f, 0.0f,
		25.5f, 0.0f, 0xffff0000, 0.0f, 0.0f,
		-25.5f, 25.5f, 0xffff0000, 0.0f, 0.0f);

	// saving the mesh (list of triangles) in _mesh
	_mesh = AEGfxMeshEnd();
}