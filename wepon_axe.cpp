#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"scene.h"
#include"wepon_axe.h"
#include"player.h"
#include"animationModel.h"
#include"swordtrail.h"
#include"input.h"
#include"enemy.h"

void Axe::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\axe.obj");

	m_DepthEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_TrailPosition = m_Position;

	//抜刀時
	m_Scale = D3DXVECTOR3(4.5f, 4.5f, 4.5f);
	m_Position = D3DXVECTOR3(0.0f, 6.0f, 8.0f);
	m_Rotation = D3DXVECTOR3(2.7f, 1.5f, 0.999f);

	//納刀時
	/*m_Scale = D3DXVECTOR3(4.5f, 4.5f, 4.5f);
	m_Position = D3DXVECTOR3(0.0f, 6.0f, 8.0f);
	m_Rotation = D3DXVECTOR3(2.7f, 1.5f, 0.999f);*/

}

void Axe::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Axe::Update()
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
	/*	m_Scale = D3DXVECTOR3(4.5f, 4.5f, 4.5f);
		m_Position = D3DXVECTOR3(11.0f, -1.0f, -1.0f);
		m_Rotation = D3DXVECTOR3(-3.6f, -1.8f, 2.0f);*/
	}
	else
	{
		bone = animationmodel->GetBone("mixamorig:Spine");
		/*m_Scale = D3DXVECTOR3(4.5f, 4.5f, 4.5f);
		m_Position = D3DXVECTOR3(20.0f, 6.0f, -14.0f);
		m_Rotation = D3DXVECTOR3(0.5f, 0.0f, 2.0f);*/
	}
	bone->WorldMatrix;
	m_Parent = animationmodel->ConvertMatrix(bone->WorldMatrix);
	 
	//position変換
	D3DXVECTOR3 boneWorldPosition;
	boneWorldPosition.x = m_Parent._41;
	boneWorldPosition.y = m_Parent._42;
	boneWorldPosition.z = m_Parent._43;

	//scale変換
	D3DXVECTOR3  x = D3DXVECTOR3(m_Parent._11, m_Parent._12, m_Parent._13);
	D3DXVECTOR3  y = D3DXVECTOR3(m_Parent._21, m_Parent._22, m_Parent._23);
	D3DXVECTOR3  z = D3DXVECTOR3(m_Parent._31, m_Parent._32, m_Parent._33);

	boneWorldPosition.x = D3DXVec3Length(&x);
	boneWorldPosition.y = D3DXVec3Length(&y);
	boneWorldPosition.z = D3DXVec3Length(&z);
	
	////剣のワールド座標
	D3DXVECTOR3 swordWorldPosition = boneWorldPosition;

	
	/*if (player->GetSwordDrawn())
	{
		if (swordWorldPosition.x - m_Scale.x / 100 - 0.5f < enemy->GetPosition().x &&
			enemy->GetPosition().x < swordWorldPosition.x + m_Scale.x / 100 + 0.5f &&
			swordWorldPosition.z - m_Scale.z / 100 - 0.5f < enemy->GetPosition().z &&
			enemy->GetPosition().z < swordWorldPosition.z + m_Scale.z / 100 + 0.5f)
		{
			m_swordhit = true;
		}
		else
		{
			m_swordhit = false;
		}
	}*/
	

	/*if (swordWorldPosition.x  < enemy->GetPosition().x &&
		enemy->GetPosition().x < swordWorldPosition.x  &&
		swordWorldPosition.z  < enemy->GetPosition().z &&
		enemy->GetPosition().z < swordWorldPosition.z )
	{
		m_swordhit = true;
	}
	else
	{
		m_swordhit = false;
	}*/

	//GUIにパラメータ表示
	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Axe");
	ImGui::InputFloat3("Position", m_Position);
	ImGui::InputFloat3("WorldPosition", swordWorldPosition);
	ImGui::InputFloat3("Ratation", m_Rotation);
	ImGui::InputFloat3("Scale", m_Scale);
	ImGui::Checkbox("Hit", &m_swordhit);
	ImGui::End();




}

void Axe::Draw()
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

