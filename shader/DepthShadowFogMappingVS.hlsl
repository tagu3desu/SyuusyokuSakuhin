
#include "common.hlsl"



void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	Out.Position = mul(In.Position, wvp);


	//���_�̖@�������[���h�s��ŕϊ�����
	float4 worldNormal, normal;

	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);
	Out.Normal = worldNormal;

	//��������
	float light = -dot(Light.Direction.xyz, worldNormal.xyz);
	light = saturate(light);
	
	//���_�J���[�͂��̂܂܃R�s�[
	Out.Diffuse = light;
	Out.Diffuse.a = In.Diffuse.a;

	//���͂��ꂽUV���W���o�͐�֑������
    Out.TexCoord = In.TexCoord;
	Out.Tangent = float4(0.0, 0.0, 0.0, 0.0);
	Out.Binormal = float4(0.0, 0.0, 0.0, 0.0);

	//���C�g�J�������猩�����_���W���쐬
	matrix lightwvp;
	lightwvp = mul(World, Light.View);
	lightwvp = mul(lightwvp, Light.Projection);

	Out.ShadowPosition = mul(In.Position, lightwvp);
	
	//���[���h�ϊ��������_���W���o��
    Out.WorldPosition = mul(In.Position, World);
}
