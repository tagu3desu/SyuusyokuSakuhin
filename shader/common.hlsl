


cbuffer WorldBuffer : register(b0)
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}




struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;
	bool TextureEnable;
	float2 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}




struct LIGHT
{
	bool Enable;
	bool3 Dummy;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
	
    matrix view; //ライトカメラのビュー行列
    matrix Projection; //ライトカメラのプロジェクション行列
};

cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}

cbuffer CameraBuffer : register(b5)
{
    float4 CameraPosition;
	
    float4 FogParam;
    float4 FogColor;
    float4 GroundFogColor;
}

struct PARAMETER
{
    float4 hp;
    float4 lostColor;
    float4 baseColor;
    float4 diffColor;
	
    float4 stamina;
    float4 baseStaminaColor;
	
    float4 collidercollor;
	
    float4 weponaura;
};

cbuffer ParamBuffer : register(b6)
{
    float dissolveThreshold;
    float disolveRange;
    float2 dummy;
	
   
	
    PARAMETER param;
}



struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
	
    float4 Tangent : TANGENT0;
    float4 Binormal : BINORMAL0;
	
    uint Instanceld : SV_InstanceID;
};


struct PS_IN
{
	float4 Position		: SV_POSITION;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
	
    float4 WorldPosition : POSITION0;
    float4 Normal : NORMAL0;
    float4 Tangent : TANGENT0;
    float4 Binormal : BINORMAL0;

	
    float4 ShadowPosition : POSITION1; //ライトカメラから見たピクセルの座標
};


struct VS_SKINIG_IN
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
	
    float4 Tangent : TANGENT0;
    float4 Binormal : BINORMAL0;
    uint4  Index : INDEX0;
    float4 Weight : WEIGHT0;
    
    uint Instanceld : SV_InstanceID;
};


cbuffer BoneBuffer : register(b7)
{
    float4x4 bonrTransform[200];
}


StructuredBuffer<float3> Position : register(t2);