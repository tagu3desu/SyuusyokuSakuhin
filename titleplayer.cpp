#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"scene.h"
#include"titleplayer.h"
#include"bullet.h"
#include"box.h"
#include"cylinder.h"
#include"audio.h"
#include"shadow.h"
#include"animationModel.h"
#include"meshField.h"
#include"camera.h"
#include"enemy.h"
#include"staminagage.h"
#include"hpgage.h"
#include"potioncount.h"



void TitlePlayer::Init()
{

	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Paladin J Nordstrom.fbx");

	//�[����ԃ��[�V����
	m_Model->LoadAnimation("asset\\model\\Walking.fbx", "Walk");
	m_Model->LoadAnimation("asset\\model\\Standard Run.fbx", "Run");
	m_Model->LoadAnimation("asset\\model\\Unarmed Idle 01.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Great Sword Jump.fbx", "Jump");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Death.fbx", "IsDead");
	m_Model->LoadAnimation("asset\\model\\Sprinting Forward Roll.fbx", "IsRoll");

	//�����[�V����
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Walk.fbx", "SwordWalk");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Run.fbx", "SwordRun");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Idle.fbx", "SwordIdle");
	m_Model->LoadAnimation("asset\\model\\Sheath Sword 2.fbx", "onSword");
	m_Model->LoadAnimation("asset\\model\\Sheath Sword 1.fbx", "offSword");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Slash.fbx", "SlashAttack");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Slash2.fbx", "SlashAttack2");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Slash3.fbx", "SlashAttack3");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield RotationAttack .fbx", "RotationAttack");
	m_Model->LoadAnimation("asset\\model\\ComboAttack1.fbx", "ComboAttack1");
	m_Model->LoadAnimation("asset\\model\\ComboAttack2.fbx", "ComboAttack2");
	m_Model->LoadAnimation("asset\\model\\ComboAttack3.fbx", "ComboAttack3");
	m_Model->LoadAnimation("asset\\model\\GreatSwordBackWalk.fbx", "BackWalk");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield BlockStart.fbx", "StartGuard");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Block Idle.fbx", "IsGuard");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield BlockEnd.fbx", "EndGuard");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Impact.fbx", "GuardImpact");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield HitSmallAttack.fbx", "HitSmallImpact");


	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	
	m_Scale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);
	//m_MoveVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = 0.1f;

	m_DepthEnable = true;
	m_ReflectEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\DepthShadowMappingPS.cso");


	m_OnWeponSE = AddComponent<Audio>();
	m_OnWeponSE->Load("asset\\audio\\���𔲂�.wav");

	m_OffWeponSE = AddComponent<Audio>();
	m_OffWeponSE->Load("asset\\audio\\������ɂ��܂�.wav");

	m_RunSoundBGM = AddComponent<Audio>();
	m_RunSoundBGM->Load("asset\\audio\\�Z�̋R�m������.wav");

	m_WalkSoundBGM = AddComponent<Audio>();
	m_WalkSoundBGM->Load("asset\\audio\\�Z�̋R�m������.wav");

	m_AttackSE = AddComponent<Audio>();
	m_AttackSE->Load("asset\\audio\\�ؓ��E�U��.wav");

	m_Time = 0.0f;
	m_BlendTime = 0.0f;
	m_AnimationDelay = 0.0f;
	m_ConboNumber = 0;
	m_HP = 0;


	directionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	directionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_sworddrawn = false;
	m_comboCount=0;
	m_Stamina = 0;

	GameObject::Init();
}

void TitlePlayer::Uninit()
{
	GameObject::Uninit();

	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}


void TitlePlayer::Update()
{
	Scene* scene = Manager::GetScene();

	directionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	directionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_move = false;
	
	GameObject::Update();
	D3DXVECTOR3 oldPosition = m_Position;


	

	Camera* camera = scene->GetGameObject<Camera>();
	cameraFoward = camera->GetForward();
	cameraRight = camera->GetRight();
	cameraFoward.y = 0.0f;
	cameraRight.y = 0.0f;
	D3DXVec3Normalize(&cameraRight, &cameraRight);
	D3DXVec3Normalize(&cameraFoward, &cameraFoward);



	//GUI�Ƀp�����[�^�\��
	/*ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Player");
	ImGui::InputFloat3("Position", m_Position);
	ImGui::InputFloat3("BPosition", m_BonePos);
	ImGui::InputFloat3("Scale", m_Scale);
	ImGui::InputInt("HP", &m_HP);
	ImGui::InputFloat("AnimationDelay", &m_AnimationDelay);
	ImGui::InputInt("count", &hitcount);
	ImGui::Checkbox("Collision", &m_PlayerHitEnemy);
	ImGui::Checkbox("Move", &m_move);
	ImGui::Checkbox("Run", &m_run);
	ImGui::Checkbox("Attack", &m_attack);
	ImGui::Checkbox("Idle", &m_idle);
	ImGui::Checkbox("Guard", &m_isGuard); 
	ImGui::Checkbox("EndGuard", &m_EndGuard);
	ImGui::Checkbox("InpactGuard", &m_InpactGuard);
	ImGui::End();*/



	switch (m_PlayerState)
	{
	case TITLEPLAYER_STATE_GROUND:
		UpdateGround();
		break;
	default:
		break;
	}

	






	////���b�V���t�B�[���h�Ƃ̏Փ˔���
	float groundHeight = 0.0f;
	//auto meshField = scene->GetGameObject<MeshField>();
	//groundHeight = meshField->GetHeight(m_Position);


	//�~��
	std::vector<Cylinder*> Cylinders = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cylinder : Cylinders)//�͈�for
	{
		D3DXVECTOR3 postion = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();

		D3DXVECTOR3 direction2 = m_Position - postion;
		direction2.y = 0.0f;
		float length = D3DXVec3Length(&direction2);

		if (length < scale.x)
		{
			if (m_Position.y < postion.y + scale.y - 0.5f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}
			else
			{

				groundHeight = postion.y + scale.y + groundHeight; //�㔻��
			}
			break;
		}

	}

	

	
	////�l�p���@
	std::vector<Box*> boxes = scene->GetGameObjects<Box>();

	for (Box* box : boxes)
	{


		D3DXVECTOR3 position = box->GetPosition();
		D3DXVECTOR3 scale = box->GetScale();
		D3DXVECTOR3 right = box->GetRight();	//X������
		D3DXVECTOR3 forward = box->GetForward();	//Z������
		D3DXVECTOR3 direction = m_Position - position; //�����̂���v���C���[�܂ł̕����x�N�g��

		float obbx = D3DXVec3Dot(&direction, &right);	//X�����������v���C���[����
		float obbz = D3DXVec3Dot(&direction, &forward); //Z�����������v���C���[����

		//OBB
		if (fabs(obbx) < scale.x && fabs(obbz) < scale.z)
		{
			if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
			{
				// �ǂ̖@���x�N�g�����v�Z
				D3DXVECTOR3 wallNormal(1.0f, 0.0f, 0.0f);

				// �v���C���[�̈ړ��x�N�g���ƕǂ̖@���x�N�g���̎ˉe���v�Z
				D3DXVECTOR3 projectedVector = m_MoveVector - D3DXVec3Dot(&m_MoveVector, &wallNormal) * wallNormal;

				// �v���C���[�̈ʒu��␳
				m_Position.x = oldPosition.x + projectedVector.x;
				m_Position.z = oldPosition.z + projectedVector.z;
			}
			else
			{
				groundHeight = position.y + groundHeight + scale.y * 2.0f;
			}
			break;

		}

		//AABB
		//// �Ǐ�̓���̓_�i�����ł͕ǂ̒����j����v���C���[�ւ̃x�N�g�����v�Z
		//D3DXVECTOR3 wallToPlayer = m_Position - D3DXVECTOR3(position.x, m_Position.y, position.z);

		//// �ǂ̖@���x�N�g�����v�Z
		//D3DXVECTOR3 wallNormal(0.0f, 0.0f, 0.0f);
		//if (D3DXVec3LengthSq(&wallToPlayer) > 0.0001f)
		//{
		//	D3DXVec3Normalize(&wallNormal, &wallToPlayer);
		//}

		//if (position.x - scale.x - 1.0f < m_Position.x &&
		//	m_Position.x < position.x + scale.x + 1.0f &&
		//	position.z - scale.z - 1.0f < m_Position.z &&
		//	m_Position.z < position.z + scale.z + 1.0f)
		//{
		//	if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
		//	{
		//		// �ǂ̖@���x�N�g�����v�Z
		//		D3DXVECTOR3 wallNormal(1.0f, 0.0f, 0.0f);

		//		// �v���C���[�̈ړ��x�N�g���ƕǂ̖@���x�N�g���̎ˉe���v�Z
		//		D3DXVECTOR3 projectedVector = m_MoveVector - D3DXVec3Dot(&m_MoveVector, &wallNormal) * wallNormal;

		//		// �v���C���[�̈ʒu��␳
		//		m_Position.x = oldPosition.x + projectedVector.x;
		//		m_Position.z = oldPosition.z + projectedVector.z;
		//	}
		//	else
		//	{
		//		groundHeight = position.y + groundHeight + scale.y * 2.0f;
		//	}
		//	break;
		//}
	}



	

	

	//�d��
	m_Velocity.y -= 0.015f;

	//�W�����v�p�ړ�
	m_Position += m_Velocity;

	//�ڒn
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_IsGround = true;
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}
	else
	{
		m_IsGround = false;
	}

	

	GameObject::Update();

}

void TitlePlayer::Draw()
{
	GameObject::Draw();

	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	
	//�}�g���N�X�ݒ�
	D3DXMATRIX  world,scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_Matrix = scale * rot * trans;//�e��matrix��������
	Renderer::SetWorldMatrix(&m_Matrix);

	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendTime);


	m_Time += 0.7;
	
	

	if (m_BlendTime < 1.0f)
	{
		m_BlendTime += 0.1f;
	}

	m_Model->Draw();

	GameObject::Draw();
}


void TitlePlayer::UpdateGround()
{
	
	Scene* scene = Manager::GetScene();
	Enemy* enemy = scene->GetGameObject<Enemy>();


	if (Input::GetKeyTrigger('Y')/*(VK_LBUTTON)*/ && !m_sworddrawn)
	{
		
			if (m_NextAnimationName != "onSword")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "onSword";
				//m_OnWeponSE->Volume(0.01f);
				//m_OnWeponSE->Play();
				m_BlendTime = 0.0f;
			}
			m_onSword = true;
			m_sworddrawn = true;
		
	}

	if (Input::GetKeyTrigger('R'))
	{
		if (m_sworddrawn)//�[��
		{
			if (m_NextAnimationName != "offSword")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "offSword";
				//m_OffWeponSE->Volume(0.01f);
				//m_OffWeponSE->Play();
				m_BlendTime = 0.0f;
			}
			m_offSword = true;
			
		}
		
	}

	if (m_onSword)
	{
		m_AnimationDelay++;
		if (m_AnimationDelay > 35)
		{
			m_onSword = false;
			m_AnimationDelay = 0;
		}
	
	}
	if (m_offSword)
	{
		m_AnimationDelay++;
		if (m_AnimationDelay > 50)
		{
			m_sworddrawn = false;
			m_AnimationDelay = 0;
			m_offSword = false;
		}

	}

	

	if (!m_move &&  !m_onSword && !m_offSword)
	{
		m_run = false;
		m_idle = true;
		//m_WalkSoundBGM->Stop();
		//m_RunSoundBGM->Stop();
		if (m_sworddrawn)
		{
			if (m_NextAnimationName != "SwordIdle")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "SwordIdle";
				m_comboCount = 0;
				m_BlendTime = 0.0f;
			}
		}
		else
		{
			if (m_NextAnimationName != "Idle")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Idle";
				m_comboCount = 0;
				m_BlendTime = 0.0f;
			}
		}
		
	}
	//x,z�����Z���܂�
	D3DXVECTOR3 direction = directionX + directionZ;


	//���K�����܂�
	D3DXVec3Normalize(&direction, &direction);

	//Positon��Speed���Z���܂�
	m_Position += direction *m_speed;


}

