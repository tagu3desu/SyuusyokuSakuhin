#include"main.h"
#include"renderer.h"
#include"collider.h"
#include"player.h"
#include"scene.h"
#include"manager.h"
void Collider::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\box.obj");

	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");
	
}

void Collider::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Collider::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	m_Position = player->GetBonePosition();
	m_Scale = player->GetScale()*10;
	//GUIにパラメータ表示
	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Box");

	ImGui::InputFloat3("Position", m_Position);	
	ImGui::InputFloat3("Scale", m_Scale);
	ImGui::End();
}

void Collider::Draw()
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

	m_Model->Draw();
}