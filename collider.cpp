#include"main.h"
#include"renderer.h"
#include"collider.h"
#include"scene.h"
#include"manager.h"
#include"wepon_sword.h"
#include"input.h"
Model* Collider::m_Model;
bool m_ColliderEnable;
void Collider::Load()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\colliderver3.obj");
};

void Collider::Init()
{
	//m_Scale = D3DXVECTOR3(0.0f, 0.00f, 0.0f);
	//m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ScaleOffset = (D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\collidervertexLightingPS.cso");	
}

void Collider::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Collider::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Collider::Update()
{
	if (Input::GetKeyTrigger('4'))
	{
		m_ColliderEnable = true;
	}
	if (Input::GetKeyTrigger('5'))
	{
		m_ColliderEnable = false;
	}
}

	


void Collider::Draw()
{
	if (!m_ColliderEnable)
	{
		GameObject::Draw();
		//入力レイアウト
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


		PARAMETER parameter;
		parameter.collidercollor = D3DXCOLOR(m_ColliderColor.r, m_ColliderColor.g, m_ColliderColor.b, m_ColliderColor.a);
		Renderer::SetParameter(parameter);


		//マトリクス設定
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
			m_Matrix = scale * rot * trans * m_Parent * m_BoneMatrix;
		}
		
		
		Renderer::SetWorldMatrix(&m_Matrix);

		Renderer::SetATCEnable(true);

		m_Model->Draw();

		Renderer::SetATCEnable(false);
	}
	
}



//A(obb1)とB(obb2)のOBB当たり判定関数
bool Collider::CollisionChecker(GameObject* obb1, GameObject* obb2 ,float offsetscale)
{
	//Aの軸に格納
	D3DXVECTOR3 NAe1 = obb1->GetColliderRight(), Ae1 = NAe1 * (obb1->GetColliderScale().x * offsetscale);
	D3DXVECTOR3 NAe2 = obb1->GetColliderUp(), Ae2 = NAe2 * (obb1->GetColliderScale().y * offsetscale);
	D3DXVECTOR3 NAe3 = obb1->GetColliderForward(), Ae3 = NAe3 * (obb1->GetColliderScale().z * offsetscale);

	//Bの軸に格納
	D3DXVECTOR3 NBe1 = obb2->GetColliderRight(), Be1 = NBe1 * (obb2->GetColliderScale().x * offsetscale);
	D3DXVECTOR3 NBe2 = obb2->GetColliderUp(), Be2 = NBe2 * (obb2->GetColliderScale().y * offsetscale);
	D3DXVECTOR3 NBe3 = obb2->GetColliderForward(), Be3 = NBe3 * (obb2->GetColliderScale().z * offsetscale);

	//中心座標の距離
	D3DXVECTOR3 Interval = obb1->GetColliderPosition() - obb2->GetColliderPosition();

	//分離軸の計算//

	//投影線分の長さ
	float rA, rB, L;
	//外積分離軸
	D3DXVECTOR3 Cross;

	//Ae1
	rA = D3DXVec3Length(&Ae1);
	rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe1));
	//判定
	if (L > rA + rB)
		return false; // 衝突していない

	//Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe2));
	//判定
	if (L > rA + rB)
		return false;

	//Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe3));
	//判定
	if (L > rA + rB)
		return false;

	//Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = fabs(D3DXVec3Dot(&Interval, &NBe1));
	//判定
	if (L > rA + rB)
		return false;

	//Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = fabs(D3DXVec3Dot(&Interval, &NBe2));
	//判定
	if (L > rA + rB)
		return false;

	//Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NBe3));
	//判定
	if (L > rA + rB)
		return false;

	//C11
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	//判定
	if (L > rA + rB)
		return false;

	//C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	//判定
	if (L > rA + rB)
		return false;

	//C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	//判定
	if (L > rA + rB)
		return false;

	//C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	//判定
	if (L > rA + rB)
		return false;

	//C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	//判定
	if (L > rA + rB)
		return false;

	//C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	//判定
	if (L > rA + rB)
		return false;

	//C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	//判定
	if (L > rA + rB)
		return false;

	//C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	//判定
	if (L > rA + rB)
		return false;

	//C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2, 0);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2, 0);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	//判定
	if (L > rA + rB)
		return false;

	//判定

	return true; // 衝突している
}

// 投影線分長関数 //
// 分離軸に投影された軸成分から投影線分長を算出
// 分離軸Sepは標準化されていること
float Collider::LenSegOnSeparateAxis(D3DXVECTOR3* Sep, D3DXVECTOR3* e1, D3DXVECTOR3* e2, D3DXVECTOR3* e3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	//e3が0だった時0をr3に代入
	//0以外だった時fabsの計算をしr3に代入
	float r3 = e3 ?  (fabs(D3DXVec3Dot(Sep, e3))) : 0;

	return r1 + r2 + r3;
}

//bool OBBvsOBB(GameObject* obb1, GameObject* obb2)
//{
//	//
//}


