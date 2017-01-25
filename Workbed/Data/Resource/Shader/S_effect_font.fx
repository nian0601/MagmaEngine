#include "S_u_variables.fx"

Matrix SpriteOrientation;
float4 SpriteSizeAndHotSpot;
float4 SpritePositionAndScale;

static const float OUTLINE_MIN_VALUE0 = 0.0;
static const float OUTLINE_MIN_VALUE1 = 0.5;
static const float OUTLINE_MAX_VALUE0 = 0.5;
static const float OUTLINE_MAX_VALUE1 = 1;
static const float4 OUTLINE_COLOR = {1.f, 0.f, 0.f, 1.f};
static const bool USE_OUTLINE = false;

static const float OUTER_GLOW_MIN_VALUE = 0.0;
static const float OUTER_GLOW_MAX_VALUE = 0.5;
static const float4 GLOW_COLOR = {0.f, 1.f, 0.f, 1.f};
static const bool USE_GLOW = true;
static const float2 GLOW_UV_OFFSET = {0.005f, 0.005f};



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
	finalPosition.x -= 300;
	finalPosition.y -= 40;
	finalPosition.xy *= 1;
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
	float distAlphaMask = texColor.a;

	if(USE_OUTLINE &&
		(distAlphaMask >= OUTLINE_MIN_VALUE0 && distAlphaMask <= OUTLINE_MAX_VALUE1))
	{
		float oFactor = 1.0;
		if(distAlphaMask <= OUTLINE_MIN_VALUE1)
		{
			oFactor = smoothstep(OUTLINE_MIN_VALUE0, OUTLINE_MIN_VALUE1, distAlphaMask);
		}
		else
		{
			oFactor = smoothstep(OUTLINE_MAX_VALUE1, OUTLINE_MAX_VALUE0, distAlphaMask);
		}

		texColor = lerp(texColor, OUTLINE_COLOR, oFactor);
	}

	if(USE_GLOW)
	{
		float4 glowColor = AlbedoTexture.Sample(pointSampling, aInput.Tex + GLOW_UV_OFFSET);

		glowColor = GLOW_COLOR + smoothstep(OUTER_GLOW_MIN_VALUE, OUTER_GLOW_MAX_VALUE, glowColor.a);
		texColor = lerp(glowColor, texColor, distAlphaMask);
	}

	texColor.a *= smoothstep(0.0, 0.5, distAlphaMask);

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