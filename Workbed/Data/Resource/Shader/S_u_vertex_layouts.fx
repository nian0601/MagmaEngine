struct Vertex_ColoredCube
{
	float4 Position : POSITION;
	float4 Color : COLOR0;
};

struct Pixel_ColoredCube
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR0;
};

struct Vertex_ColoredCube_Normal
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
};

struct Pixel_ColoredCube_Normal
{
	float4 Position : SV_POSITION;
	float3 Normal : NORMAL;
};


struct Vertex_Model
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float2 Tex : TEXCOORD;
	float3 BiNormal : BINORMAL;
	float3 Tangent : TANGENT;
};

struct Pixel_Model
{
	float4 Position : SV_POSITION;
	float3 Normal : NORMAL;
	float2 Tex : TEXCOORD;
	float3 BiNormal : BINORMAL;
	float3 Tangent : TANGENT;
	float4 WorldPosition : POSITION;
};

struct Vertex_Quad
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct Pixel_Quad
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

struct Vertex_LightMesh
{
	float4 Position : POSITION;
};

struct Pixel_LightMesh
{
	float4 Position : SV_POSITION;
	float4 Tex : POSITION;
};

struct GBuffer
{
	float4 AlbedoMetalness;
	float4 NormalRoughness;
	float Depth;
};