//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "ConstantBuffers.hlsli"

PixelShaderPassThroughInput main(VertextShaderInput input)
{
	PixelShaderPassThroughInput output = (PixelShaderPassThroughInput)0;

	output.position = mul(mul(mul(input.position, world), view), projection);
    output.textureUV = input.textureUV;
	// Vertex pos in view space (normalize in pixel shader)
	output.vertexToEye = -mul(mul(input.position, world), view).xyz;

    return output;
}