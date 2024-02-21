#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"scene.h"
#include"wepon_shield.h"
#include"player.h"
#include"animationModel.h"
#include"input.h"
#include"collider.h"
#include"title.h"
#include"rockeffect.h"
void Shield::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\MetalShield.obj");

	m_DepthEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");



	//m_Scale = D3DXVECTOR3(1.0f/0.1f, 1.0f / 0.1f, 1.0f / 0.1f);
	m_Scale = D3DXVECTOR3(1.0f / 0.01f, 1.0f / 0.01f, 1.0f / 0.01f);
	m_Position = D3DXVECTOR3(5.0f, 12.0f, 3.0f);
	m_Rotation = D3DXVECTOR3(-2.9f, -4.25f, 1.5f);
	
	m_Scene = Manager::GetScene();

	if (!Title::GetCheckTitle())
	{
		
		m_ShieldCollider = m_Scene->AddGameObject<Collider>(COLLIDER_LAYER);
		m_ShieldCollider->SetScale(D3DXVECTOR3(0.45f, 0.25f, 0.60f));
		m_ShieldCollider->SetTag(ITEM_TAG);
	}

	
}

void Shield::Uninit()
{
	m_Model->Unload();
	delete m_Model;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Shield::Update()
{
	Player* player = m_Scene->GetGameObject<Player>();
	AnimationModel* animationmodel;


	if (!Title::GetCheckTitle())
	{
		m_RockEffect = m_Scene->GetGameObject<RockEffect>();
		//盾に当たり判定をつける
		m_ShieldCollider->SetMatrix(m_Matrix);
		m_ShieldCollider->SetColliderInfo(m_ShieldCollider->GetMatrix(), false);

		if (m_RockEffect != nullptr)
		{
			if (m_ShieldCollider->CollisionChecker(this, m_RockEffect, 0.7f))
			{
				m_ShieldHit = true;
				m_ShieldCollider->SetColliderColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
			else
			{
				m_ShieldHit = false;
				m_ShieldCollider->SetColliderColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
		}
	}
	



	animationmodel = player->GetAnimationModel();
	BONE* bone;
	bone = animationmodel->GetBone("mixamorig:LeftForeArm");
	bone->WorldMatrix;
	m_Parent = animationmodel->ConvertMatrix(bone->WorldMatrix);
	 

	D3DXVECTOR3 boneWorldPosition;
	boneWorldPosition.x = m_Parent._41;
	boneWorldPosition.y = m_Parent._42;
	boneWorldPosition.z = m_Parent._43;

	D3DXVECTOR3 shieldRelativePosition(0.0f, 0.0f, 10.0f);
	//剣のワールド座標
	D3DXVECTOR3 shieldWorldPosition = boneWorldPosition + shieldRelativePosition;


	//GUIにパラメータ表示
	/*ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Shield");
	ImGui::InputFloat3("Position", m_Position);
	ImGui::InputFloat3("WorldPosition", shieldWorldPosition);
	ImGui::InputFloat3("Ratation", m_Rotation);
	ImGui::InputFloat3("Scale", m_Scale);
	ImGui::End();*/
}

void Shield::Draw()
{
	
	Player* player = m_Scene->GetGameObject<Player>();

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
	D3DXMATRIX  scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	
	
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_Matrix = scale * rot * trans * m_Parent * player->GetMatrix();
	
	

	Renderer::SetWorldMatrix(&m_Matrix);

	m_Model->Draw();
}