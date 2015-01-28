//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "pch.h"
#include "Sphere.h"

using namespace DirectX;

//----------------------------------------------------------------------

Sphere::Sphere()
{
    m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_radius = 1.0f;
    Update();
}

//----------------------------------------------------------------------

Sphere::Sphere(
    DirectX::XMFLOAT3 position,
    float radius
    )
{
    m_position = position;
    m_radius = radius;
    Update();
}

//-------------------------------------------------------------------------

void Sphere::UpdatePosition()
{
	XMStoreFloat4x4(
		&m_modelMatrix,
		XMMatrixScaling(m_radius, m_radius, m_radius) *
		XMMatrixTranslation(m_position.x, m_position.y, m_position.z)
		);
}
//----------------------------------------------------------------------

void Sphere::Update()
{
    XMStoreFloat4x4(
        &m_modelMatrix,
        XMMatrixScaling(m_radius, m_radius, m_radius) *
        XMMatrixTranslation(m_position.x, m_position.y, m_position.z)
        );
}


