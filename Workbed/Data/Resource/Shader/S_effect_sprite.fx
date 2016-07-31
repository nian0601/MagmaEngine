#include "S_u_variables.fx"

Matrix SpriteOrientation;
float4 SpriteSizeAndHotSpot;
float4 SpritePositionAndScale;

Pixel_FullscreenQuad VertexShader_Sprite(Vertex_FullscreenQuad aInput)
{
	float2 size = SpriteSizeAndHotSpot.xy / 2;
	float2 hotspot = SpriteSizeAndHotSpot.zw;
	float2 position = SpritePositionAndScale.xy;
	float2 scale = SpritePositionAndScale.zw;

	float4 finalPosition = aInput.Pos;

	finalPosition.xy *= size;
	finalPosition.xy += size;
	finalPosition.xy -= hotspot;

	finalPosition.xy *= scale;
	finalPosition.xy += position;

	finalPosition = mul(finalPosition, Projection);

	finalPosition.xy -= 1;

	Pixel_FullscreenQuad output = (Pixel_FullscreenQuad)0;
	output.Pos = finalPosition;
	output.Tex = aInput.Tex;
		
	return output;
}

float4 PixelShader_Sprite(Pixel_FullscreenQuad aInput) : SV_Target
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