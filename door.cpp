#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"scene.h"
#include"camera.h"
#include"door.h"
#include"input.h"


void Door::Init()
{
	GameObject::Init();
	m_Model = new Model();
	m_Model->Load("asset\\model\\doorVer2.obj");
	m_Scale = D3DXVECTOR3(0.013f, 0.013f, 0.01f);
	

	m_DepthEnable = true;

	m_Threshold = 1.0f;
	m_dissolveEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\dissolvePS.cso");

	dissolveflag = false;
}

void Door::Uninit()
{
	GameObject::Uninit();

	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Door::Update()
{
	GameObject::Update();
	
	if (Input::GetKeyTrigger('L'))
	{
		dissolveflag = true;
	}

	if (dissolveflag)
	{
		m_Threshold -= 0.005f;
	}
	
	/*if (m_Threshold == 0)
	{
		m_Threshold = 1.0f;
	}*/

	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	D3DXVECTOR3 cameraposition;
	cameraposition = camera->GetPosition();
	m_Position.z = (cameraposition.z + 10.0f);
}

void Door::Draw()
{
	GameObject::Draw();
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//// テクスチャ設定
	/*ID3D11ShaderResourceView* depthShadowTexture = Renderer::GetDepthShadowTexture();
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &depthShadowTexture);*/

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	PARAMETER param;
	ZeroMemory(&param, sizeof(param));
	param.dissolveThreshold = m_Threshold;
	param.disolveRange = 0.1f;
	Renderer::SetParameter(param);

	Renderer::SetATCEnable(true);
	m_Model->Draw();
	Renderer::SetATCEnable(false);
}

