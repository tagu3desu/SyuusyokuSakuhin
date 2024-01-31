
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
TextureCube g_TextureEnvCube : register(t2); //�L���[�u�}�b�v�󂯎��
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
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
    
    //�C���˃x�N�g��������}�b�s���O�p�̃e�N�X�`�����W���쐬����
    //float2 envTexCoord;
    //envTexCoord.x = -refv.x * 0.5 + 0.5f;
    //envTexCoord.y = -refv.y * 0.5 + 0.5f;
    
    //float4 envColor = g_TextureEnv.Sample(g_SamplerState, envTexCoord);
    
    
    float4 envColor = g_TextureEnvCube.Sample(g_SamplerState, refv);
    
	//�e�N�X�`������F���T���v�����O����
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb = (envColor.rgb * 1.0) + (outDiffuse.rgb * 0.1);
    outDiffuse.a = In.Diffuse.a;
}
