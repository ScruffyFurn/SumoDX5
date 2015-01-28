//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "ConstantBuffers.hlsli"

float4 main(PixelShaderSkyInput input) : SV_Target
{
	float4 litColor = skyMap.Sample(linearSampler, input.texCoord);

	if (fogStart > 0)
	{
		float dist = distance(input.vertexToEye, cameraPosition.xyz);
		float fogLerp = saturate((dist - fogStart) / fogRange);
		litColor = lerp(litColor, fogColor, fogLerp);
	}

	return litColor;
}
