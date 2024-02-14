
#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//法線を正規化して格納する
	float4 normal = normalize(In.Normal);

	//ランバート
    float light = -dot(Light.Direction.xyz, normal.xyz);
   

	//テクスチャから色をサンプリングする
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= light;
    outDiffuse.a *= In.Diffuse.a;
   
	//ブリンフォン鏡面反射
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
	
	//光の反射ベクトル
    float3 refv = (Light.Direction.xyz, normal.xyz);
	refv = normalize(refv);

	//リムライティング
    float rim = 1.0f + dot(eyev, normal.xyz);
    rim = pow(rim, 3) * 2.0f;
    rim = saturate(rim);
	
   
    
    outDiffuse.r += rim * param.weponaura.r;
    outDiffuse.b += rim * param.weponaura.g;
    outDiffuse.g += rim * param.weponaura.b;
    outDiffuse.a = In.Diffuse.a;
}
