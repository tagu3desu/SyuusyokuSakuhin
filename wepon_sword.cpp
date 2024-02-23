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
#include"collider.h"
#include"title.h"
#include"bladeefect1.h"
#include"bladeefect2.h"
#include"dummy.h"
#include"trail.h"
#include"camera.h"
#include"audio.h"

ID3D11Buffer* SwordTopVertex::m_VertexBuffer;
void Sword::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\MetalSword.obj");

	
	m_DepthEnable = true;
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\pixelLightingRimPS.cso");

	//納刀時
	m_Scale = D3DXVECTOR3(110.0f, 110.0f, 1.0f / 0.01f);
	m_Position = D3DXVECTOR3(20.0f, 6.0f, -14.0f);
	m_Rotation = D3DXVECTOR3(0.5f, 0.0f, 2.0f);


	m_Scene = Manager::GetScene();

	//斬れ味関連
	m_WeponSharpnes = SHARPNES_BLUE; //初期切れ味青
	m_Durability = MAX_DURABILITY;			 //武器耐久値


	if (!Title::GetCheckTitle())
	{
		m_SwordTrail = m_Scene->AddGameObject<Trail>();
		m_SwordTopVertex = m_Scene->AddGameObject<SwordTopVertex>();

		m_SwordCollider = m_Scene->AddGameObject<Collider>(COLLIDER_LAYER);
		m_SwordCollider->SetScale(D3DXVECTOR3(0.2f, 0.2f, 1.0f));
		m_SwordCollider->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.2f));
	}

	m_SmallAttackHitSE = AddComponent<Audio>();
	m_SmallAttackHitSE->Load("asset\\audio\\SE\\刀剣・斬る08.wav");

	m_NormalAttackHitSE = AddComponent<Audio>();
	m_NormalAttackHitSE->Load("asset\\audio\\SE\\刀剣・斬る06.wav");

	m_BigAttackHitSE = AddComponent<Audio>();
	m_BigAttackHitSE->Load("asset\\audio\\SE\\刀剣・斬る07.wav");
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
	Player* player = m_Scene->GetGameObject<Player>();
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();
	m_Camera = m_Scene->GetGameObject<Camera>();


	if (!Title::GetCheckTitle())
	{
		//剣に当たり判定をつける
		m_SwordCollider->SetMatrix(m_Matrix);
		SetColliderInfo(m_SwordCollider->GetMatrix());
		//軌跡セット
		m_SwordTrail->SetTrail(m_SwordTopVertex->GetTopVertexPostion(), GetBottomVertexPostion(), player->GetPlayerAttackCollider());

		//斬れ味の管理
		switch (m_WeponSharpnes)
		{
		case SHARPNES_RED:
			m_WeponDamage = 0.0f;
			m_HitStopTime = 0.0f;
			break;
		case SHARPNES_YELLOW:
			m_WeponDamage = 3.0f;
			m_HitStopTime = 5.0f;
			break;
		case SHARPNES_GREEN:
			m_WeponDamage = 5.0f;
			m_HitStopTime = 10.0f;
			break;
		case SHARPNES_BLUE:
			m_WeponDamage = 8.0f;
			m_HitStopTime = 10.0f;
			break;
		default:
			break;
		}

		if (m_Durability <= 20)		//武器の耐久20%以下
		{
			if (m_WeponSharpnes != SHARPNES_RED)
			{
				m_WeponSharpnes = SHARPNES_RED;
				m_DownSharpnessFlag = true;
			}
			
		}
		else if (m_Durability <= 40)	//武器の耐久40%以下
		{
			if (m_WeponSharpnes != SHARPNES_YELLOW)
			{
				m_WeponSharpnes = SHARPNES_YELLOW;
				m_DownSharpnessFlag = true;
			}

			
		}
		else if (m_Durability <= 80)	//武器の耐久80%以下
		{
			if (m_WeponSharpnes != SHARPNES_GREEN)
			{
				m_WeponSharpnes = SHARPNES_GREEN;
				m_DownSharpnessFlag = true;
			}
			
		}
		else if(m_Durability <= 100)
		{
			if (m_WeponSharpnes != SHARPNES_BLUE)
			{
				m_WeponSharpnes = SHARPNES_BLUE;
			}
		}

		if (m_DownSharpnessFlag)
		{
			m_FrameWait++;
			if (m_FrameWait >= 100)
			{
				m_FrameWait = 0.0f;
				m_DownSharpnessFlag = false;
			}
		}

		if (player->GetSharpnessUpFlag())
		{
			m_Durability = MAX_DURABILITY;
		}

		
		//敵との当たり判定
		if (enemy != nullptr)
		{
			
			if (m_SwordCollider->CollisionChecker(this, enemy, 0.7f))
			{
				
				m_SwordCollider->SetColliderColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				if (player->GetPlayerAttackCollider() && !m_InvincibilityFlag)
				{
					if (player->GetPlayerAttackNumber() == 1)
					{
						
						m_NormalAttackHitSE->Volume(Scene::m_SEVolume);
						m_NormalAttackHitSE->PlaySE();
						m_Camera->Shake(0.05f);

					}

					if (player->GetPlayerAttackNumber() == 2)
					{
						m_SmallAttackHitSE->Volume(Scene::m_SEVolume * 0.3f);
						m_SmallAttackHitSE->PlaySE();
						m_Camera->Shake(0.02f);
					}

					if (player->GetPlayerAttackNumber() == 3)
					{
						m_BigAttackHitSE->Volume(Scene::m_SEVolume * 0.2f);
						m_BigAttackHitSE->PlaySE();
						m_Camera->Shake(0.1f);
					}
					
					m_ResultDamege = player->GetAttackMagnification()* m_WeponDamage;
					m_Durability -= 20.0f;
					m_Swordhit = true;
					m_NormalAttackHitSE->Volume(Scene::m_SEVolume * 0.2f);
					m_NormalAttackHitSE->PlaySE();
					enemy->SetDamage(m_ResultDamege);
					BladeEffect1* bladeeffect1 = m_Scene->AddGameObject<BladeEffect1>(EFFECT_LAYER);
					SwordTopVertex* swordvertex = m_Scene->GetGameObject<SwordTopVertex>();
					bladeeffect1->SetScale(D3DXVECTOR3(6.5f, 6.5f, 6.5f));
					bladeeffect1->SetPosition(swordvertex->GetTopVertexPostion());
					player->SetHitStop(true);
				}
				
			}
			else
			{
				m_Swordhit = false;
				m_SwordCollider->SetColliderColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
		}


		


		//ヒットストップ時間の設定
		if (player->GetHitStopFlag())
		{
			player->SetHitStopTime(m_HitStopTime);
		}


		if (m_Swordhit)
		{
			m_InviciblilityStartFlag = true;
		}
		if (m_InviciblilityStartFlag)
		{
			m_InvincibilityTime++;
			if (m_InvincibilityTime <= 15)
			{
				m_InvincibilityFlag = true;
			}
			else
			{
				m_InvincibilityFlag = false;
				m_InviciblilityStartFlag = false;
				m_InvincibilityTime = 0;
			}
		}

		if (player->GetSwordDrawn())
		{
			m_ModelRimColor = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			m_ModelRimColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		}

	}



	//プレイヤーにくっつける処理
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
	D3DXVECTOR3 worldposition = MatrixtoPosition(m_Matrix);


	m_BottomVertex = worldposition;

	/*ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Sword");
	ImGui::Checkbox("HIt", &m_Swordhit);
	ImGui::InputInt("HitCoolTime", &m_InvincibilityTime);
	ImGui::End();*/

}

void Sword::Draw()
{
	Scene* scene = Manager::GetScene();
	Player* player = m_Scene->GetGameObject<Player>();
	

	GameObject::Draw();
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	
	PARAMETER parameter;
	parameter.weponcolor = D3DXCOLOR(m_ModelRimColor.r, m_ModelRimColor.g, m_ModelRimColor.b, m_ModelRimColor.a);
	Renderer::SetParameter(parameter);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);	
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_Matrix = scale * rot * trans * m_Parent * player->GetMatrix();



	Renderer::SetWorldMatrix(&m_Matrix);

	m_Model->Draw();
}


void SwordTopVertex::Init()
{
	m_Scene = Manager::GetScene();
	m_Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.7f);
}
void SwordTopVertex::Load()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);	//左奥
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 0.0f, 1.0f);	//右奥
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1.0f, 0.0f, -1.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ設定
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void SwordTopVertex::Unload()
{
	m_VertexBuffer->Release();
}

void SwordTopVertex::Uninit()
{
}

void SwordTopVertex::Update()
{
	
	Sword* sword = m_Scene->GetGameObject<Sword>();
	

	m_Parent = sword->GetMatrix();
	m_TopVertex = MatrixtoPosition(m_Matrix);
}

void SwordTopVertex::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_Matrix = scale * rot * trans * m_Parent;
	Renderer::SetWorldMatrix(&m_Matrix);

	

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
}