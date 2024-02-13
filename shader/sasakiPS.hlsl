
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureDepthShadow : register(t1);
TextureCube g_TextureEnvCube : register(t2);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�e�N�X�`������F���T���v�����O����
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse *= In.Diffuse;

    	//�@���𐳋K�����Ċi�[����
    float4 normal = normalize(In.Normal);

	//�����o�[�g
    float light = -dot(Light.Direction.xyz, normal.xyz);
    light = saturate(light);

    //�A�����x�N�g�������
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);

    //�B���˃x�N�g�������
    float3 refv = reflect(eyev, normal.xyz);
    refv = normalize(refv);    
    
    float4 envColor = g_TextureEnvCube.Sample(g_SamplerState, refv);
    
	//�e�N�X�`������F���T���v�����O����
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb = (envColor.rgb * 0.5) + (outDiffuse.rgb * 1.0);
    outDiffuse.a = In.Diffuse.a;

    In.ShadowPosition.xyz /= In.ShadowPosition.w;
    In.ShadowPosition.x = In.ShadowPosition.x * 0.5 + 0.5;
    In.ShadowPosition.y = -In.ShadowPosition.y * 0.5 + 0.5;

    float depth = g_TextureDepthShadow.Sample(g_SamplerState, In.ShadowPosition.xy);
	
    if (depth < In.ShadowPosition.z - 0.001)
    {
        outDiffuse.rgb *= 0.5;
    }

}
