#include "S_u_variables.fx"

Matrix SpriteOrientation;
float4 SpriteSizeAndHotSpot;
float4 SpritePositionAndScale;

static const float OUTLINE_MIN_VALUE0 = 0.3;
static const float OUTLINE_MIN_VALUE1 = 0.4;
static const float OUTLINE_MAX_VALUE0 = 0.5;
static const float OUTLINE_MAX_VALUE1 = 0.6;
static const float4 OUTLINE_COLOR = {0.f, 0.f, 0.f, 1.f};
static const bool USE_OUTLINE = true;

static const float OUTER_GLOW_MIN_VALUE = 0.0;
static const float OUTER_GLOW_MAX_VALUE = 0.5;
static const float4 GLOW_COLOR = {0.f, 1.f, 0.f, 1.f};
static const bool USE_GLOW = false;
static const float2 GLOW_UV_OFFSET = {0.005f, 0.005f};

static const float SMOOTHING = 1.0/16.0;

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
	//finalPosition.x -= 50;
	//finalPosition.y -= 40;
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
	float4 texColor = {1.f, 1.f, 1.f, 1.f};
	float distAlphaMask = AlbedoTexture.SampleLevel(linearSampling, aInput.Tex, 0).a;

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


	float alpha = smoothstep(0.55 - SMOOTHING, 0.55 + SMOOTHING, distAlphaMask);
	
	texColor.a = alpha;
	//return float4(1.f, 1.f, 1.f, alpha);

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