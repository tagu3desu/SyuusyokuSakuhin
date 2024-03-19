#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"camera.h"
#include"player.h"
#include"scene.h"
#include"input.h"
#include"title.h"
#include"enemy.h"
#include"debug.h"
#include"result.h"
#include"inputx.h"
#include"tutorialenemy.h"
void Camera::Init()
{	
	
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -20.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	m_RotationY = 1.7f;
	m_FogStart =100.0f;
	m_FogEnd= 500.0f;
	m_FogHeight =300.0f;

	m_FogColor = D3DXCOLOR(0.4f, 0.0f, 0.0f, 0.0f);
	m_GroundFogColor = D3DXCOLOR(0.2f, 0.0f, 0.0f, 0.0f);

	m_Scene = Manager::GetScene();
}
void Camera::Update()
{
	
	Player* player = m_Scene->GetGameObject<Player>();
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();
	TutorialEnemy* tutoriaruenemy = m_Scene->GetGameObject<TutorialEnemy>();
	DebugSystem* debug = m_Scene->GetGameObject<DebugSystem>();
	
	

	if (enemy != nullptr)
	{
		if (enemy->GetDead())
		{
			if (m_FogHeight >= 5)
			{
				m_FogHeight -= 1.0f;
			}
			if (m_FogColor.a <= 1.5f)
			{
				m_FogColor += D3DXCOLOR(0.003f, 0.003f, 0.003f, 0.003f);
			}
			
			if (m_GroundFogColor.a <=1.5f)
			{
				m_GroundFogColor += D3DXCOLOR(0.003f, 0.003f, 0.003f, 0.003f);
			}
			
		}
	}
	
	if (tutoriaruenemy != nullptr)
	{
		if (tutoriaruenemy->GetDead())
		{
			if (m_FogHeight >= 5)
			{
				m_FogHeight -= 1.0f;
			}
			if (m_FogColor.a <= 1.5f)
			{
				m_FogColor += D3DXCOLOR(0.003f, 0.003f, 0.003f, 0.003f);
			}

			if (m_GroundFogColor.a <= 1.5f)
			{
				m_GroundFogColor += D3DXCOLOR(0.003f, 0.003f, 0.003f, 0.003f);
			}

		}
	}

	


	if (Title::GetCheckTitle())
	{
		m_RotationX = 0.1f;
		m_RotationY = 3.7f;
	}
	else
	{
		if (Input::GetKeyPress('E') || InputX::GetThumbRightX(0) >= 0.2)
		{
			m_RotationX -= 0.1f;
		}
		if (Input::GetKeyPress('Q') || InputX::GetThumbRightX(0) <= -0.2)
		{
			m_RotationX += 0.1f;
		}
		if (Input::GetKeyPress(VK_UP) || InputX::GetThumbRightY(0) >= 0.2)
		{
			m_RotationY += 0.1f;
		}
		if (Input::GetKeyPress(VK_DOWN) || InputX::GetThumbRightY(0) <= -0.2)
		{
			m_RotationY -= 0.1f;
		}
	}

	

	

	//トップビュー	
	if (Input::GetKeyPress('L'))
	{
		// カメラの位置から敵の位置を向くベクトルを計算
		D3DXVECTOR3 length = m_Target - m_Position;
		D3DXVec3Normalize(&length, &length);//正規化

		// カメラの向きを設定
		m_Rotation.x = asinf(length.y) * -1.0f;
		m_Rotation.y = atan2f(length.x, length.z);

		//注視点は敵
		m_Target = enemy->GetPosition();
		//ポジションはプレイヤー
		m_Position = player->GetPosition() - GetForward() * 5.0f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	}
	else if (enemy != nullptr &&  enemy->GetDead() && !m_DeathCamera)
	{
		m_FrameWait++;
		if (m_FrameWait < 120)
		{
			m_EnemyCameraRotationX += 0.01f;
			m_Target = enemy->GetPosition() + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
			m_Position = m_Target + enemy->GetForward() * 13.0f + enemy->GetForward() * 1.5f + enemy->GetUp() * (1.5f * m_EnemyCameraRotationX);
		}
		else if (m_FrameWait <= 240)
		{
			m_EnemyCameraRotationY += 0.01f;
			m_Target = enemy->GetPosition() + D3DXVECTOR3(0.0f, 1.0f, 0.0f) + enemy->GetForward() * 3.0f;
			m_Position = m_Target + enemy->GetForward() * 13.0f + enemy->GetRight() * (15.0f + m_EnemyCameraRotationY) + D3DXVECTOR3(0.0f, 6.0f, 0.0f);
		}
		else if (m_FrameWait <= 300)
		{
			m_EnemyCameraRotationY += 0.01f;
			m_Target = enemy->GetPosition() + D3DXVECTOR3(0.0f, 1.0f, 0.0f) + enemy->GetForward() * 3.0f;
			m_Position = m_Target + enemy->GetForward() * 6.0f + enemy->GetRight() * (15.0f + m_EnemyCameraRotationY) + D3DXVECTOR3(0.0f, 16.0f, 0.0f);
		}

		if (300 <= m_FrameWait)
		{
			m_DeathCamera = true;
		}
		
		
	}
	else if (tutoriaruenemy != nullptr && tutoriaruenemy->GetDead() && !m_DeathCamera)
	{
		m_FrameWait++;
		if (m_FrameWait < 120)
		{
			m_EnemyCameraRotationX += 0.01f;
			m_Target = tutoriaruenemy->GetPosition() + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
			m_Position = m_Target + tutoriaruenemy->GetForward() * 13.0f + tutoriaruenemy->GetForward() * 1.5f + tutoriaruenemy->GetUp() * (1.5f * m_EnemyCameraRotationX);
		}
		else if (m_FrameWait <= 240)
		{
			m_EnemyCameraRotationY += 0.01f;
			m_Target = tutoriaruenemy->GetPosition() + D3DXVECTOR3(0.0f, 1.0f, 0.0f) + tutoriaruenemy->GetForward() * 3.0f;
			m_Position = m_Target + tutoriaruenemy->GetForward() * 13.0f + tutoriaruenemy->GetRight() * (15.0f + m_EnemyCameraRotationY) + D3DXVECTOR3(0.0f, 6.0f, 0.0f);
		}
		else if (m_FrameWait <= 300)
		{
			m_EnemyCameraRotationY += 0.01f;
			m_Target = tutoriaruenemy->GetPosition() + D3DXVECTOR3(0.0f, 1.0f, 0.0f) + tutoriaruenemy->GetForward() * 3.0f;
			m_Position = m_Target + tutoriaruenemy->GetForward() * 6.0f + tutoriaruenemy->GetRight() * (15.0f + m_EnemyCameraRotationY) + D3DXVECTOR3(0.0f, 16.0f, 0.0f);
		}

		if (300 <= m_FrameWait)
		{
			m_DeathCamera = true;
		}


	}
	else if (player!= nullptr &&  player->GetPlayerDead() && !m_DeadCameraFlag)
	{
		m_DeadCameraY += 0.001f;
		m_RotationX += 0.01f;
		m_Target = player->GetCameraCorrectionPosition();
		m_Position = m_Target + D3DXVECTOR3(sin(m_RotationX) * -1.0f, m_RotationY * (4.0f + m_DeadCameraY), -cos(m_RotationX) * 1.0f);
		m_FrameWait++;
		if (m_FrameWait > 200)
		{
			m_DeadCameraFlag = true;
			m_RotationX -= 2.0f;
		}
		
		
	}
	else if (!Title::GetCheckTitle())
	{
		//トップビュー
		if (player->GetPlayerAttack())
		{
			m_Target = player->GetCameraCorrectionPosition() + player->GetUp() * 3.0f;
		}
		else
		{
			m_Target = player->GetPosition() + player->GetUp() * 3.0f;
		}
		m_Position = m_Target + D3DXVECTOR3(sin(m_RotationX) * 8.0f, m_RotationY*1.0f, -cos(m_RotationX) * 8.0f);
		
	}


	if (Title::GetCheckTitle())
	{
		m_Target = player->GetPosition() + D3DXVECTOR3(-2.0f,0.0f,0.0f);
		m_Position = m_Target + D3DXVECTOR3(sin(m_RotationX) * 10.0f, m_RotationY, -cos(m_RotationX) * 4.0f)  ;
	}

	

	//カメラシェイク
	m_ShakeOffset = sinf(m_ShakeTime * 1.5f) * m_ShakeAmplitude;
	m_ShakeTime++;
	m_ShakeAmplitude *= 0.8f;
	

}
void Camera::Draw()
{
	//ビューマトリクス設定
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 position = m_Position + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);
	D3DXVECTOR3 target = m_Target + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);

	D3DXMatrixLookAtLH(&m_ViewMatrix, &position, &target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f/*視野*/, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);

	//Fog設定
	CAMERA camera;
	camera.Position = D3DXVECTOR4(m_Position.x, m_Position.y, m_Position.z,1.0f);
	camera.FogParam.x = m_FogStart;
	camera.FogParam.y = m_FogEnd;
	camera.FogParam.z = m_FogHeight;
	camera.FogParam.w = 0.0f;
	//camera.FogColor = D3DXCOLOR(0.3f, 0.0f, 0.0f,1.0f);
	//camera.GroundFogColor= D3DXCOLOR(0.1f, 0.0f, 0.0f, 1.0f);
	camera.FogColor = m_FogColor;
	camera.GroundFogColor= m_GroundFogColor;
	Renderer::SetCameraPosition(camera);



}

bool Camera::CheckView(D3DXVECTOR3 Position)
{
	D3DXMATRIX vp, invvp;
	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);


	D3DXVECTOR3 v, v1, v2, n;

	v =	Position- m_Position;

	//左面判定
	{
		v1 = wpos[0] - m_Position;
		v2 = wpos[2] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
			return false;
	}

	//右面判定
	{
		v1 = wpos[3] - m_Position;
		v2 = wpos[1] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
			return false;
	}

	return true;
}

