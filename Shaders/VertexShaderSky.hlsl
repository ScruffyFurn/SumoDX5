//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "ConstantBuffers.hlsli"

PixelShaderSkyInput main(VertextShaderInput input)
{
	PixelShaderSkyInput output = (PixelShaderSkyInput)0;

	//Set Pos to xyww instead of xyzw, so that z will always be 1 (furthest from camera)
	output.position = mul(mul(mul(input.position, world), view), projection).xyww;
	// Vertex pos in view space (normalize in pixel shader)
	output.vertexToEye = -mul(mul(input.position, world), view).xyz;
	output.texCoord = input.position;

	return output;
}