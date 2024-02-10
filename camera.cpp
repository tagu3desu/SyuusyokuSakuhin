#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"camera.h"
#include"player.h"
#include"scene.h"
#include"input.h"
#include"title.h"
void Camera::Init()
{	
	
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -20.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	m_RotationY = 1.7f;
	m_FogStart =100.0f;
	m_FogEnd= 500.0f;
	m_FogHeight =100.0f;
}
void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	


	if (Input::GetKeyPress('J'))
	{
		m_FogHeight += 1.0f;
	}
	if (Input::GetKeyPress('H'))
	{
		m_FogHeight -= 1.0f;
	}

	/*ImGui::Begin("Camera");
	ImGui::InputFloat("FogStart", &m_FogStart);
	ImGui::InputFloat("FogEnd", &m_FogEnd);
	ImGui::InputFloat("FogHeight", &m_FogHeight);
	ImGui::InputFloat("RotationX", &m_RotationX);
	ImGui::InputFloat("RotationY", &m_RotationY);
	ImGui::End();*/

	
#if 1 //デバッグ
	//-0.3,6.8

	if (Title::GetCheckTitle())
	{
		m_RotationX = 0.1f;
		m_RotationY = 3.7f;
		/*if (Input::GetKeyPress(VK_RIGHT))
		{
			m_RotationX -= 0.1f;
		}
		if (Input::GetKeyPress(VK_LEFT))
		{
			m_RotationX += 0.1f;
		}
		if (Input::GetKeyPress(VK_UP))
		{
			m_RotationY += 0.1f;
		}
		if (Input::GetKeyPress(VK_DOWN))
		{
			m_RotationY -= 0.1f;
		}*/
	}
	else
	{
		if (Input::GetKeyPress(VK_RIGHT))
		{
			m_RotationX -= 0.1f;
		}
		if (Input::GetKeyPress(VK_LEFT))
		{
			m_RotationX += 0.1f;
		}
		if (Input::GetKeyPress(VK_UP))
		{
			m_RotationY += 0.1f;
		}
		if (Input::GetKeyPress(VK_DOWN))
		{
			m_RotationY -= 0.1f;
		}
		/*if (Input::GetKeyPress(VK_UP) && m_RotationY < 6.7)
		{
			m_RotationY += 0.1f;
		}
		if (Input::GetKeyPress(VK_DOWN) && m_RotationY > 1.5)
		{
			m_RotationY -= 0.1f;
		}*/
	}

	
#else //本番用
	if (!Title::GetCheckTitle())
	{
		m_Rotation -= GetMouseCursorPosX() / 600;
		if (1.5f <= m_RotationY && m_RotationY <= 6.6)
		{
			m_RotationY += GetMouseCursorPosY() / 600;
		}

		if (m_RotationY < 1.5f)
		{
			m_RotationY = 1.5f;
		}
		if (m_RotationY > 6.6f)
		{
			m_RotationY = 6.6f;
		}
	}
#endif 

	


	

	//トップビュー	
	

	if (!Title::GetCheckTitle())
	{
		m_Target = player->GetPosition();
		m_Position = m_Target + D3DXVECTOR3(sin(m_RotationX) * 8.0f, m_RotationY, -cos(m_RotationX) * 8.0f);
	}
	if (Title::GetCheckTitle())
	{
		m_Target = player->GetPosition() + D3DXVECTOR3(-2.0f,0.0f,0.0f);
		m_Position = m_Target + D3DXVECTOR3(sin(m_RotationX) * 10.0f, m_RotationY, -cos(m_RotationX) * 4.0f);
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
	camera.FogColor = D3DXCOLOR(0.0f, 0.0f, 0.4f,1.0f);
	camera.GroundFogColor= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
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

