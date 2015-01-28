#include "pch.h"
#include "GenericMesh.h"
#include "../Utilities/DirectXSample.h"
#include "../Rendering/ConstantBuffers.h"

GenericMesh::GenericMesh(ID3D11Buffer*  vertexBuffer, ID3D11Buffer*  indexBuffer, unsigned int numVertex, unsigned int numIndex)
{
	m_vertexBuffer = vertexBuffer;
	m_indexBuffer = indexBuffer;
	m_vertexCount = numVertex;
	m_indexCount = numIndex;
}