#include "S_u_variables.fx"

Matrix Orientation;
float4 SizeAndHotSpot;
float4 PositionAndScale;

Pixel_Quad VertexShader_Sprite(Vertex_Quad aInput)
{
	float2 size = SizeAndHotSpot.xy / 2;
	float2 hotspot = SizeAndHotSpot.zw;
	float2 position = PositionAndScale.xy;
	float2 scale = PositionAndScale.zw;

	float4 finalPosition = aInput.Pos;

	finalPosition.xy *= size;
	finalPosition.xy += size;
	finalPosition.xy -= hotspot;

	finalPosition.xy *= scale;
	finalPosition.xy += position;

	finalPosition = mul(finalPosition, Projection);

	finalPosition.xy -= 1;

	Pixel_Quad output = (Pixel_Quad)0;
	output.Pos = finalPosition;
	output.Tex = aInput.Tex;
		
	return output;
}

float4 PixelShader_Sprite(Pixel_Quad aInput) : SV_Target
{
	return AlbedoTexture.Sample(pointSampling, aInput.Tex);
}

technique11 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VertexShader_Sprite()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PixelShader_Sprite()));
	}
}