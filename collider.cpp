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

	

	m_ColliderScale = MatrixtoScale(m_Matrix);
	m_ColliderPosition = MatrixtoPosition(m_Matrix);

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
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
		m_Matrix = scale * rot * trans * m_Parent;
		Renderer::SetWorldMatrix(&m_Matrix);

		Renderer::SetATCEnable(true);

		m_Model->Draw();

		Renderer::SetATCEnable(false);
	}
	
}



