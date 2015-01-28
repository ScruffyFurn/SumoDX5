/// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "pch.h"
#include "Face.h"

using namespace DirectX;

//----------------------------------------------------------------------

Face::Face()
{
    SetPlane(
        XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT3(1.0f, 0.0f, 0.0f),
        XMFLOAT3(0.0f, 1.0f, 0.0f)
        );
}

//----------------------------------------------------------------------

Face::Face(
    XMFLOAT3 origin,
    XMFLOAT3 p1,
    XMFLOAT3 p2
    )
{
    SetPlane(origin, p1, p2);
}

//--------------------------------------------------------------------------------

void Face::SetPlane(
    XMFLOAT3 origin,
    XMFLOAT3 p1,
    XMFLOAT3 p2
    )
{
    m_position = origin;
    XMStoreFloat3(&m_widthVector, XMLoadFloat3(&p1) - XMLoadFloat3(&origin));
    XMStoreFloat3(&m_heightVector, XMLoadFloat3(&p2) - XMLoadFloat3(&origin));

    m_point[0] = m_position;
    m_point[1] = p1;
    m_point[3] = p2;
    XMStoreFloat3(&m_point[2], XMLoadFloat3(&p1) + XMLoadFloat3(&m_heightVector));

    XMStoreFloat(&m_width, XMVector3Length(XMLoadFloat3(&m_widthVector)));
    XMStoreFloat(&m_height, XMVector3Length(XMLoadFloat3(&m_heightVector)));

    XMStoreFloat3(
        &m_normal,
        XMVector3Normalize(
            XMVector3Cross(
                XMLoadFloat3(&m_widthVector),
                XMLoadFloat3(&m_heightVector)
                )
            )
        );
    UpdateMatrix();
}

//--------------------------------------------------------------------------------

void Face::UpdatePosition()
{
    m_point[0] = m_position;
    XMStoreFloat3(&m_point[1], XMLoadFloat3(&m_position) + XMLoadFloat3(&m_widthVector));
    XMStoreFloat3(&m_point[3], XMLoadFloat3(&m_position) + XMLoadFloat3(&m_heightVector));
    XMStoreFloat3(&m_point[2], XMLoadFloat3(&m_point[1]) + XMLoadFloat3(&m_heightVector));

    XMStoreFloat4x4(
        &m_modelMatrix,
        XMMatrixScaling(m_width, m_height, 1.0f) *
        XMLoadFloat4x4(&m_rotationMatrix) *
        XMMatrixTranslation(m_position.x, m_position.y, m_position.z)
        );
}

//--------------------------------------------------------------------------------

void Face::UpdateMatrix()
{
    // Determine the Model transform for the cannonical face to align with the position
    // and orientation of the defined face.  The cannonical face geometry is
    // a rectangle at the origin extending 1 unit in the +X and 1 unit in the +Y direction.

    XMVECTOR w = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);
    XMVECTOR h = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
    XMVECTOR epsilon = XMVectorReplicate(0.0001f);
    XMVECTOR width = XMVectorScale(XMLoadFloat3(&m_widthVector), 1.0f / m_width);
    XMVECTOR height = XMVectorScale(XMLoadFloat3(&m_heightVector), 1.0f / m_height);
    XMMATRIX mat1 = XMMatrixIdentity();
    XMMATRIX mat2 = XMMatrixIdentity();

    // Determine the necessary rotation to align the widthVector with the +X axis.
    // Then apply the rotation to the cannonical H vector (+Y).
    if (!XMVector3NearEqual(w, width, epsilon))
    {
        float angle1 = XMVectorGetX(
            XMVector3AngleBetweenVectors(w, width)
            );

        if (XMVector3NearEqual(w, XMVectorNegate(width), epsilon))
        {
            // The angle between w and width is ~180 degrees, so
            // pick a axis of rotation perpendicular to the W vector.
            mat1 = XMMatrixRotationAxis(XMVector3Orthogonal(w), angle1);
            h = XMVector3TransformCoord(h, mat1);
        }
        else if ((angle1 * angle1) > 0.025)
        {
            // Take the cross product between the w and width vectors to
            // determine the axis to rotate that is perpendicular to both vectors.
            XMVECTOR axis1 = XMVector3Cross(w, width);
            mat1 = XMMatrixRotationAxis(axis1, angle1);
            h = XMVector3TransformCoord(h, mat1);
        }
    }

    // Determine the necessary rotation to align the transformed heightVector
    // with the transformed H vector.
    if (!XMVector3NearEqual(h, height, epsilon))
    {
        float angle2 = XMVectorGetX(
            XMVector3AngleBetweenVectors(h, height)
            );

        if (XMVector3NearEqual(h, XMVectorNegate(height), epsilon))
        {
            // The angle between the h' and height vectors is ~180 degrees,
            // so rotate around the width vector to keep it aligned in the right
            // place.
            mat2 = XMMatrixRotationAxis(width, angle2);
        }
        else if ((angle2 * angle2) > 0.025)
        {
            // Take the cross product between the h' and height vectors
            // to determine the axis to rotate that is perpendicular to both vectors.
            XMVECTOR axis2 = XMVector3Cross(h, height);
            mat2 = XMMatrixRotationAxis(axis2, angle2);
        }
    }
    XMStoreFloat4x4(&m_rotationMatrix, mat1 * mat2);

    // Generate the composite matrix to scale, rotate and translate to cannonical
    // face geometry to be positioned correctly in world space.
    XMStoreFloat4x4(
        &m_modelMatrix,
        XMMatrixScaling(m_width, m_height, 1.0f) *
        mat1 *
        mat2 *
        XMMatrixTranslation(m_position.x, m_position.y, m_position.z)
        );
}

//--------------------------------------------------------------------------------