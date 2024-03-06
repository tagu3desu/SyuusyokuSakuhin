#include"main.h"
#include"renderer.h"
#include"spherecollider.h"
#include"scene.h"
#include"manager.h"
#include"input.h"
Model* SphereCollider::m_Model;

void SphereCollider::Load()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\object\\spherecollider.obj");
	
};

void SphereCollider::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\collidervertexLightingPS.cso");	
}

void SphereCollider::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void SphereCollider::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void SphereCollider::Update()
{
}

	


void SphereCollider::Draw()
{
	
		Renderer::SetRssetEnable(true);
		GameObject::Draw();
		//���̓��C�A�E�g
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//�V�F�[�_�ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


		PARAMETER parameter;
		parameter.collidercollor = D3DXCOLOR(m_ColliderColor.r, m_ColliderColor.g, m_ColliderColor.b, m_ColliderColor.a);
		Renderer::SetParameter(parameter);


		//�}�g���N�X�ݒ�
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, m_Scale.x , m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x , m_Position.y, m_Position.z );
		
		if (!m_BoneEnable)
		{
			m_Matrix = scale * rot * trans * m_Parent;
		}
		else
		{
			m_Matrix = scale * rot * trans * m_BoneMatrix * m_Parent ;
		}
		
		
		Renderer::SetWorldMatrix(&m_Matrix);

		Renderer::SetATCEnable(true);

		if (m_ColliderEnable)
		{
		m_Model->Draw();
		}
		Renderer::SetRssetEnable(false);
		Renderer::SetATCEnable(false);
	
	
}



//A(obb1)��B(obb2)��OBB�����蔻��֐�
bool SphereCollider::CollisionChecker(GameObject* obb1, GameObject* obb2 ,float offsetscale)
{
	//A�̎��Ɋi�[
	D3DXVECTOR3 NAe1 = obb1->GetColliderRight(), Ae1 = NAe1 * (obb1->GetColliderScale().x * offsetscale);
	D3DXVECTOR3 NAe2 = obb1->GetColliderUp(), Ae2 = NAe2 * (obb1->GetColliderScale().y * offsetscale);
	D3DXVECTOR3 NAe3 = obb1->GetColliderForward(), Ae3 = NAe3 * (obb1->GetColliderScale().z * offsetscale);

	//B�̎��Ɋi�[
	D3DXVECTOR3 NBe1 = obb2->GetColliderRight(), Be1 = NBe1 * (obb2->GetColliderScale().x * offsetscale);
	D3DXVECTOR3 NBe2 = obb2->GetColliderUp(), Be2 = NBe2 * (obb2->GetColliderScale().y * offsetscale);
	D3DXVECTOR3 NBe3 = obb2->GetColliderForward(), Be3 = NBe3 * (obb2->GetColliderScale().z * offsetscale);

	//���S���W�̋���
	D3DXVECTOR3 Interval = obb1->GetColliderPosition() - obb2->GetColliderPosition();

	//�������̌v�Z//

	//���e�����̒���
	float rA, rB, L;
	//�O�ϕ�����
	D3DXVECTOR3 Cross;

	

	//Ae1
	rA = D3DXVec3Length(&Ae1);
	rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe1));
	float direction1 = L - (rA + rB);

	//����
	if (L > rA + rB)
		return false; // �Փ˂��Ă��Ȃ�

	//Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe2));
	float direction2 = L - (rA + rB);
	float work =Comparison(direction1, direction2);

	//����
	if (L > rA + rB)
		return false;

	//Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe3));
	float direction3 = L - (rA + rB);
	work = Comparison(work, direction3);
	//����
	if (L > rA + rB)
		return false;

	//Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = fabs(D3DXVec3Dot(&Interval, &NBe1));
	float direction4 = L - (rA + rB);
	work = Comparison(work, direction4);
	//����
	if (L > rA + rB)
		return false;

	//Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = fabs(D3DXVec3Dot(&Interval, &NBe2));
	float direction5 = L - (rA + rB);
	work = Comparison(work, direction5);
	//����
	if (L > rA + rB)
		return false;

	//Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NBe3));
	float direction6 = L - (rA + rB);
	work = Comparison(work, direction6);

	//����
	if (L > rA + rB)
		return false;

	//C11
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	float direction7 = L - (rA + rB);
	work = Comparison(work, direction7);
	//����
	if (L > rA + rB)
		return false;

	//C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	float direction8 = L - (rA + rB);
	work = Comparison(work, direction8);
	//����
	if (L > rA + rB)
		return false;

	//C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	float direction9 = L - (rA + rB);
	work = Comparison(work, direction9);
	//����
	if (L > rA + rB)
		return false;

	//C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	float direction10 = L - (rA + rB);
	work = Comparison(work, direction10);
	//����
	if (L > rA + rB)
		return false;

	//C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	float direction11 = L - (rA + rB);
	work = Comparison(work, direction11);
	//����
	if (L > rA + rB)
		return false;

	//C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	float direction12 = L - (rA + rB);
	work = Comparison(work, direction12);
	//����
	if (L > rA + rB)
		return false;

	//C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	float direction13 = L - (rA + rB);
	work = Comparison(work, direction13);
	//����
	if (L > rA + rB)
		return false;

	//C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	float direction14= L - (rA + rB);
	work = Comparison(work, direction14);
	//����
	if (L > rA + rB)
		return false;

	//C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	float direction15 = L - (rA + rB);
	work = Comparison(work, direction15);
	//����
	if (L > rA + rB)
		return false;

	//����
	return true; // �Փ˂��Ă���
}

// ���e�������֐� //
// �������ɓ��e���ꂽ���������瓊�e���������Z�o
// ������Sep�͕W��������Ă��邱��
float SphereCollider::LenSegOnSeparateAxis(D3DXVECTOR3* Sep, D3DXVECTOR3* e1, D3DXVECTOR3* e2, D3DXVECTOR3* e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	//e3��0��������0��r3�ɑ��
	//0�ȊO��������fabs�̌v�Z����r3�ɑ��
	float r3 = e3 ?  (fabs(D3DXVec3Dot(Sep, e3))) : 0;

	return r1 + r2 + r3;
}




