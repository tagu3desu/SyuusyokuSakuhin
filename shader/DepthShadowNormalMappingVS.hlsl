#include "common.hlsl"
void main(in VS_IN In, out PS_IN Out)
{
    

    matrix wvp; //�����̏�������
    wvp = mul(World, View); //1�p�X�ڂ̓��C�g�J�����̍s��
    wvp = mul(wvp, Projection); //2�p�X�ڂ͒ʏ�J�����̍s�񂪐ݒ肳���
    Out.Position = mul(In.Position, wvp); //���_���W�����[���h�ϊ����ďo��
    float4 worldNormal, normal; //�@���̃��[���h�ϊ�
    
    //Normal
    normal = float4(In.Normal.xyz, 0.0);
    worldNormal = mul(normal, World);
    Out.Normal = normalize(worldNormal); //�@�����o��
   
    
    //Tangent
    normal = float4(In.Tangent.xyz, 0.0);
    worldNormal = mul(normal, World);
    Out.Tangent = normalize(worldNormal); //�@�����o��
    
    
    //Binormal
    normal = float4(In.Binormal.xyz, 0.0);
	//�@�������[���h�ϊ�����
    worldNormal = mul(normal, World);
	//���[���h�ϊ������@���𐳋K������i�g��k���̏����폜����j
    Out.Binormal = normalize(worldNormal);
    
//��������
    float light = -dot(Light.Direction.xyz, worldNormal.xyz);
    light = saturate(light);
    Out.Diffuse = light;
    Out.Diffuse.a = In.Diffuse.a;
    Out.TexCoord = In.TexCoord; //�e�N�X�`�����W���o��
    matrix lightwvp;
    lightwvp = mul(World, Light.view); //���[���h�s�񁖃��C�g�r���[�s��
    lightwvp = mul(lightwvp, Light.Projection); //����Ɂ����C�g�v���W�F�N�V�����s��
    Out.ShadowPosition = mul(In.Position, lightwvp); //���C�g�J��������݂����_���W�o��
    
    //���_�J���[�͂��̂܂܃R�s�[
    Out.Diffuse = In.Diffuse;

	//���[���h�ϊ��������_���W���o��
    Out.WorldPosition = mul(In.Position, World);
    
}


