#include "S_u_variables.fx"

Pixel_ColoredCube VertexShader_SimpleCube(Vertex_ColoredCube aInput)
{
	Pixel_ColoredCube output = (Pixel_ColoredCube)0;
	aInput.Position.xyz *= Scale;

	Matrix mat = mul(World, ViewProjection);
	output.Position = mul(aInput.Position, mat);
	
	output.Color = aInput.Color;
	
	return output;
}

GBuffer PixelShader_SimpleCube(Pixel_ColoredCube aInput) : SV_Target
{
	//float4 AlbedoColor = aInput.Color;
	float4 AlbedoColor = float4(1.f, 1.f, 1.f, 1.f);
	//float4 AlbedoColor = float4(norm, 1.f);
	float4 AmbientOcclusion = 0.f;
	float Metalness = 1.f;
	float Roughness = 1.f;

	float3 norm = float3(1.f, 0.f, 0.f);
	GBuffer output;
	output.AlbedoMetalness = float4(AlbedoColor.xyz, Metalness);
	output.NormalRoughness = float4(norm, Roughness);
	output.Depth = aInput.Position.z;
	
	return output;
}

technique11 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VertexShader_SimpleCube()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PixelShader_SimpleCube()));
	}
}