#pragma once
#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H
#include "Component.h"
#include "AEEngine.h"

class MeshComponent :public Component
{
public:
	AEGfxVertexList* _mesh;

	MeshComponent();
	void GenerateMesh_Tri();
	virtual void InitComponent();
};

#endif // !MESHCOMPONENT_H
