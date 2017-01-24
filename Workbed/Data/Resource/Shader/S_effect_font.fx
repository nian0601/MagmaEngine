#include "S_u_variables.fx"

Matrix SpriteOrientation;
float4 SpriteSizeAndHotSpot;
float4 SpritePositionAndScale;

Pixel_Quad VertexShader_Sprite(Vertex_Quad aInput)
{
	float4 finalPosition = aInput.Pos;

	/*
	finalPosition.xy *= size;
	finalPosition.xy += size;
	finalPosition.xy -= hotspot;

	finalPosition.xy *= scale;
	finalPosition.xy += position;
	*/

	finalPosition.xy *= 0.5;
	finalPosition = mul(finalPosition, Projection);

	//finalPosition.xy -= 1;

	Pixel_Quad output = (Pixel_Quad)0;
	output.Pos = finalPosition;
	output.Tex = aInput.Tex;
		
	return output;
}

float4 PixelShader_Sprite(Pixel_Quad aInput) : SV_Target
{
	float4 texColor = AlbedoTexture.Sample(pointSampling, aInput.Tex);
	float mask = texColor.w;

	if(mask < 0.5)
		texColor.w = 0.f;
	else
		texColor.w = 1.f;

	texColor.w *= smoothstep(0.1, 0.5, mask);

	return texColor;
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