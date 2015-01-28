//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "ConstantBuffers.hlsli"

float4 main(PixelShaderPassThroughInput input) : SV_Target
{
	float4 passedColor = diffuseTexture.Sample(linearSampler, input.textureUV);
	
	if (fogStart > 0)
	{
		float dist = distance(input.vertexToEye, cameraPosition.xyz);
		float fogLerp = saturate((dist - fogStart) / fogRange);
		passedColor = lerp(passedColor, fogColor, fogLerp);
	}

	return passedColor;
}
