#include "S_u_variables.fx"

Matrix SpriteOrientation;
float4 SpriteSizeAndHotSpot;
float4 SpritePositionAndScale;

Pixel_FullscreenQuad VertexShader_Sprite(Vertex_FullscreenQuad aInput)
{
/*
	float2 size = SpriteSizeAndHotSpot.xy / 2.f;
	float2 hotspot = SpriteSizeAndHotSpot.zw / 2.f;

	float4 position = aInput.Pos;
	

	//First we set the size of the sprite
	position.xy *= size;

	//Then we need to fix the hotspot
	//Adding half of the size moves the hotspot from center to bottomleft
	position.xy += size/2;

	//After that its easier to do real hotspot-adjustments
	position.xy -= hotspot;

	//Then we do rotations
	position = mul(position, SpriteOrientation);

	//And scaling
	position.xy *= SpritePositionAndScale.zw;

	//And positioning
	position.xy += SpritePositionAndScale.xy;
	
	//Move into Projectionspace
	position = mul(position, Projection);

	//Moves the sprite from center (0, 0), to bottomleft (-1, -1)
	//position.xy -= 1;
*/

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