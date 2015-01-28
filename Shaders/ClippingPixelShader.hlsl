//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "ConstantBuffers.hlsli"

float4 main(PixelShaderInput input) : SV_Target
{
	float4 texColor = diffuseTexture.Sample(linearSampler, input.textureUV);
	clip(texColor.a < 0.1f ? -1 : 1);

	if (fogStart > 0)
	{
		float dist = distance(input.vertexToEye, cameraPosition.xyz);
		float fogLerp = saturate((dist - fogStart) / fogRange);
		texColor = lerp(texColor, fogColor, fogLerp);
	}

	return texColor;

	//show alpha channel  in the black to red colour spectrum for demo purposes.
	/*
	texColor.r = texColor.a;
	texColor.g = 0;
	texColor.b = 0;
	return texColor;
	*/
}
