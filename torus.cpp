#include"main.h"
#include"renderer.h"
#include"torus.h"

void Torus::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");


	/*D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/envmap.png",
		NULL,
		NULL,
		&m_TextureEnv,
		NULL);
	assert(m_TextureEnv);*/

	//D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
	//	"asset/texture/envmap5.dds",
	//	NULL,
	//	NULL,
	//	&m_TextureEnvCube,
	//	NULL);
	//assert(m_TextureEnvCube);

	//m_ReflectEnable = true;
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\envMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\envMappingPS.cso");


}

void Torus::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	/*m_TextureEnv->Release();
	m_TextureEnvCube->Release();*/

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Torus::Update()
{

}

void Torus::Draw()
{
	GameObject::Draw();

	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	

	m_Model->Draw();
}