
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_DisolveTexture : register(t1);


SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�@���𐳋K�����Ċi�[����
    float4 normal = normalize(In.Normal);

	//�����o�[�g
    float light = -dot(Light.Direction.xyz, normal.xyz);
    light = saturate(light);

	//�e�N�X�`������F���T���v�����O����
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= light;
    outDiffuse.a *= In.Diffuse.a;
   
	//�u�����t�H�����ʔ���
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    float3 halfv = eyev + Light.Direction.xyz;
    halfv = normalize(halfv);

    float specular = -dot(halfv, normal.xyz);
    saturate(specular);
    specular = pow(specular, 30);
    outDiffuse.rgb = saturate(outDiffuse.rgb + specular);
	
	//�f�B�]���u����
 
    //���C�v�p�e�N�X�`������T���v�����O(rgba����r�������o����)
    float dissolveValue = g_DisolveTexture.Sample(g_SamplerState, In.TexCoord);
 
    float threshold = dissolveThreshold * (1.0f + disolveRange) - disolveRange;
   
    float rate = saturate((dissolveValue - threshold) / disolveRange);
 
    outDiffuse.a = rate;

    outDiffuse.rgb = lerp(outDiffuse.rgb, float3(0.9f, 0.0f, 0.9f), 1 - pow(rate, 5));
}
