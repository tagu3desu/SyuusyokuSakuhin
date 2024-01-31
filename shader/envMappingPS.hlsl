
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
TextureCube g_TextureEnvCube : register(t2); //キューブマップ受け取り
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//法線を正規化して格納する
    float4 normal = normalize(In.Normal);

	//ランバート
    float light = -dot(Light.Direction.xyz, normal.xyz);
    light = saturate(light);

    //②視線ベクトルを作る
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);

    //③反射ベクトルを作る
    float3 refv = reflect(eyev, normal.xyz);
    refv = normalize(refv);
    
    //④反射ベクトルから環境マッピング用のテクスチャ座標を作成する
    //float2 envTexCoord;
    //envTexCoord.x = -refv.x * 0.5 + 0.5f;
    //envTexCoord.y = -refv.y * 0.5 + 0.5f;
    
    //float4 envColor = g_TextureEnv.Sample(g_SamplerState, envTexCoord);
    
    
    float4 envColor = g_TextureEnvCube.Sample(g_SamplerState, refv);
    
	//テクスチャから色をサンプリングする
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb = (envColor.rgb * 1.0) + (outDiffuse.rgb * 0.1);
    outDiffuse.a = In.Diffuse.a;
}
