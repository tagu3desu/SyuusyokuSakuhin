#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"scene.h"
#include"wepon_galbert.h"
#include"player.h"
#include"animationModel.h"
#include"input.h"


void Galbert::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\Galbert.obj");

	m_DepthEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_TrailPosition = m_Position;

	//m_Scale = D3DXVECTOR3(1.0f/0.1f, 1.0f / 0.1f, 1.0f / 0.1f);
	m_Scale = D3DXVECTOR3(1.0f / 0.03f, 1.0f / 0.03f, 1.0f / 0.03f);
	m_Position = D3DXVECTOR3(35.0f, 2.0f, -10.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 5.0f, 2.7f);
	
	

}

void Galbert::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Galbert::Update()
{
	
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	AnimationModel* animationmodel;
	animationmodel = player->GetAnimationModel();
	BONE* bone;
	bone = animationmodel->GetBone("mixamorig:RightHandPinky4");
	bone->WorldMatrix;
	m_Parent = animationmodel->ConvertMatrix(bone->WorldMatrix);
	 

	D3DXVECTOR3 trailposition;
	trailposition = m_Position;
	
	

	/*if (Input::GetKeyTrigger('U'))
	{
		SwordTrail* swordtril = scene->AddGameObject<SwordTrail>();
	}*/



	//GUIにパラメータ表示
	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Sword");
	ImGui::InputFloat3("Position", m_Position);
	ImGui::InputFloat3("Ratation", m_Rotation);
	ImGui::InputFloat3("Scale", m_Scale);
	ImGui::End();



	//player->bone= player->AnimationModel::GetBoneMatrix(player->m_Model->GetBone("mixamorig:RightHandPinky4")->SaveWorldMatrix);

}

void Galbert::Draw()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

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
	world = scale * rot * trans * m_Parent * player->GetMatrix();
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}