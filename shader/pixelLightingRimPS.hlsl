
#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�@���𐳋K�����Ċi�[����
	float4 normal = normalize(In.Normal);

	//�����o�[�g
    float light = -dot(Light.Direction.xyz, normal.xyz);
   

	//�e�N�X�`������F���T���v�����O����
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= light;
    outDiffuse.a *= In.Diffuse.a;
   
	//�u�����t�H�����ʔ���
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
	
	//���̔��˃x�N�g��
    float3 refv = (Light.Direction.xyz, normal.xyz);
	refv = normalize(refv);

	//�������C�e�B���O
    float rim = 1.0f + dot(eyev, normal.xyz);
    rim = pow(rim, 3) * 2.0f;
    rim = saturate(rim);
	
   
    
    outDiffuse.r += rim * param.weponaura.r;
    outDiffuse.b += rim * param.weponaura.g;
    outDiffuse.g += rim * param.weponaura.b;
    outDiffuse.a = In.Diffuse.a;
}
