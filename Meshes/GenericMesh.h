#pragma once

// SphereMesh:
// This class derives from MeshObject and creates a ID3D11Buffer of
// vertices and indices to represent a canonical sphere that is
// positioned at the origin with a radius of 1.0.

#include "MeshObject.h"

ref class GenericMesh : public MeshObject
{
internal:
	GenericMesh(ID3D11Buffer*  vertexBuffer, ID3D11Buffer*  indexBuffer, unsigned int numVertex, unsigned int numIndex);

};