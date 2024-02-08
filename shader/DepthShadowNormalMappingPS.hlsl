
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureDepthShadow : register(t1);
Texture2D g_TextureNormal : register(t2);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //�m�[�}���}�b�v�e�N�X�`������F���T���v�����O����
	//���̃s�N�Z���̖@���}�b�v�̃f�[�^RGBA�l���擾
    float4 normalMap = g_TextureNormal.Sample(g_SamplerState, In.TexCoord);
	//�X�P�[�����O���ĐF���x�N�g���f�[�^�֕ϊ�����
    normalMap = normalMap * 2.0 - 1.0;
    
    float4 n = normalize(In.Normal);
    float4 t = normalize(In.Tangent);
    float4 b = normalize(In.Binormal);
    float4 normal;
    normal.xyz = t.xyz * normalMap.x + b.xyz * normalMap.y + n.xyz * normalMap.z;
    normal.w = 0.0;

	//�@���𐳋K�����Ċi�[����
    normal = normalize(normal);
    
    //�����̌����Ɖ�]�ς݂̖@���Ƃœ��ς��v�Z���A�����𔽓]���ċP�x�����߂�
    float light = -dot(Light.Direction.xyz, normal.xyz);
	//�O�a���Z(0.0�`1.0�̒l�ɃN�����v����)
    light = saturate(light);
    
	//�e�N�X�`������F���T���v�����O����
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse *= In.Diffuse;

    //�}�e���A���̊g�U���𔽉f������
    outDiffuse *= Material.Diffuse;
	
	//�e�N�X�`���̐F�ɋP�x����Z����
    outDiffuse.rgb *= light;
	//�����x�͋P�x�ɉe�����Ȃ��̂ł��̂܂܎g��
    outDiffuse.a *= In.Diffuse.a;
    
    //�����x�N�g�����쐬����
    float3 evev = In.WorldPosition.xyz - CameraPosition.xyz;
    evev = normalize(evev);
	//�n�[�t�x�N�g�����쐬����i�����x�N�g���{���C�g�x�N�g���j
    float3 halfv = evev + Light.Direction.xyz;
    halfv = normalize(halfv);

    float specular = -dot(halfv, normal.xyz);
    saturate(specular);
	//�}�e���A���̃X�؃L�������x�𔽉f������
    specular = pow(specular, Material.Shininess);
	//�}�e���A���̃X�؃L�����J���[�𔽉f������
    outDiffuse.rgb = saturate(outDiffuse.rgb + specular * Material.Specular.rgb);
    
    In.ShadowPosition.xyz /= In.ShadowPosition.w;
    In.ShadowPosition.x = In.ShadowPosition.x * 0.5 + 0.5;
    In.ShadowPosition.y = -In.ShadowPosition.y * 0.5 + 0.5;

    float depth = g_TextureDepthShadow.Sample(g_SamplerState, In.ShadowPosition.xy);
	
    if (depth < In.ShadowPosition.z - 0.001)
    {
        outDiffuse.rgb *= 0.5;
    }

}
