#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"scene.h"
#include"wepon_sword.h"
#include"player.h"
#include"animationModel.h"
#include"swordtrail.h"
#include"input.h"
#include"enemy.h"
#include"trailtexture.h"





void Sword::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\MetalSword.obj");

	
	m_DepthEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");



	//抜刀時
	/*m_Scale = D3DXVECTOR3(110.0f, 110.0f, 1.0f / 0.01f);
	m_Position = D3DXVECTOR3(11.0f, -1.0f, -1.0f);
	m_Rotation = D3DXVECTOR3(-3.2f, -1.8f, 2.0f);*/

	//納刀時
	m_Scale = D3DXVECTOR3(110.0f, 110.0f, 1.0f / 0.01f);
	m_Position = D3DXVECTOR3(20.0f, 6.0f, -14.0f);
	m_Rotation = D3DXVECTOR3(0.5f, 0.0f, 2.0f);

	
}

void Sword::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Sword::Update()
{
	
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	Enemy* enemy = scene->GetGameObject<Enemy>();
	

	
	AnimationModel* animationmodel;
	animationmodel = player->GetAnimationModel();
	BONE* bone;

	if (player->GetSwordDrawn())
	{
		bone = animationmodel->GetBone("mixamorig:RightHandPinky4");
		m_Scale = D3DXVECTOR3(110.0f, 110.0f, 1.0f / 0.01f);
		m_Position = D3DXVECTOR3(11.0f, -1.0f, -1.0f);
		m_Rotation = D3DXVECTOR3(-3.6f, -1.8f, 2.0f);
	}
	else
	{
		bone = animationmodel->GetBone("mixamorig:Hips");
		m_Scale = D3DXVECTOR3(110.0f, 110.0f, 1.0f / 0.01f);
		m_Position = D3DXVECTOR3(20.0f, 6.0f, -14.0f);
		m_Rotation = D3DXVECTOR3(0.5f, 0.0f, 2.0f);
	}
	bone->WorldMatrix;
	m_Parent = animationmodel->ConvertMatrix(bone->WorldMatrix);

	////剣のワールド座標
	D3DXVECTOR3 worldposition = ExtractTranslationFromMatrix(m_Matrix);

	/*if (player->GetSwordDrawn())
	{
		TrailTexture* trail = scene->AddGameObject<TrailTexture>();
		trail->SetPosition(worldposition);
		trail->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		TrailTexture* trail2 = scene->AddGameObject<TrailTexture>();
		trail2->SetPosition(worldposition + player->GetForward() * 0.8f + player->GetRight() * 0.3f + player->GetUp() * 0.65f);
		trail2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_TopVertex = trail2->GetPosition();
		m_BottomVertex = worldposition;
	}*/
	

	
	m_BottomVertex = worldposition;

	
	//bottom = ConvertD3DXVECTOR3ToVERTEX3D(m_BottomVertex);



	




	//GUIにパラメータ表示
	ImGui::SetNextWindowSize(ImVec2(400, 250));
	ImGui::Begin("Sword");
	ImGui::InputFloat3("Position", m_Position);
	ImGui::InputFloat3("Ratation", m_Rotation);
	ImGui::InputFloat3("Scale", m_Scale);
	ImGui::InputFloat3("WorldPosition", worldposition);
	ImGui::End();


	


	



}

void Sword::Draw()
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

	m_Matrix = world;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

