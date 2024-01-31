#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"wepon_sword.h"
#include"swordtrail.h"
#include"scene.h"


void SwordTrail::Init()
{

	
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\pixelLightingPS.cso");
}

void SwordTrail::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void SwordTrail::Update()
{
	//データを更新
	for (size_t i = positionArray.size() - 1; i > 0; --i)
	{
		positionArray[i] = positionArray[i = 1];
	}
	positionArray.front() = tempPosition;
	tempPosition = PositionBuffer();

	//曲線を作る
	std::vector<PositionBuffer>usedPositionArray = GetUsedPositionArray();
	if (usedPositionArray.empty())return;
	CreateCurveVertex(usedPositionArray);

	//頂点データ更新
	float amount = 1.0f / (usedPositionArray.size() - 1);
	float v = 0;
	vertex.clear();
	vertex.resize(usedPositionArray.size() * 2);
	for (size_t i = 0, j = 0; i < vertex.size() && j < usedPositionArray.size(); i += 2, ++j)
	{
		vertex[i].position = usedPositionArray[j].swordhead;
		vertex[i].uv = XMFLOAT2(1.0f, v);
		vertex[i + 1].position = usedPositionArray[j].swordtail;
		vertex[i + 1].uv = XMFLOAT2(0.0f, v);
		v += amount;
	}
}

void SwordTrail::Draw()
{
	Scene* scene = Manager::GetScene();
	Sword* sword = scene->GetGameObject<Sword>();

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
	world = scale * rot * trans/* * sword->GetMatrix()*/;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

void SwordTrail::SetPosition(XMFLOAT3& head, XMFLOAT3& tail)
{
	tempPosition.swordhead = head;
	tempPosition.swordtail = tail;
	tempPosition.isUsed = true;
}

std::vector<PositionBuffer> SwordTrail::GetUsedPositionArray()
{
	std::vector<PositionBuffer> usedPositionArray;
	//PosArrayをいてレートして使用された位置を抽出
	for (const auto& pos : positionArray)
	{
		if (pos.isUsed)
		{
			usedPositionArray.push_back(pos);
		}
	}

	return usedPositionArray;

}

void SwordTrail::CreateCurveVertex(std::vector<PositionBuffer>& usedPositionArray)
{
	if (usedPositionArray.size() < 3 || split < 1) { return; }
	std::vector<PositionBuffer>newPositionArray;
	newPositionArray.reserve(usedPositionArray.size() + (usedPositionArray.size() - 1) * split);
	const float amount = 1.0f / (split + 1);

	PositionBuffer newPosition;
	newPositionArray.push_back(usedPositionArray.front());
	for (size_t i = 0; i < usedPositionArray.size() - 1; ++i)
	{
		float ratio = amount;
		//CutMulに使う4つの点を作る(p0,p3がないときの処理も書く)
		XMVECTOR p0Head = i == 0 ? (XMLoadFloat3(&usedPositionArray[1].swordhead) + XMLoadFloat3(&usedPositionArray[2].swordhead)) * 0.5f : XMLoadFloat3(&usedPositionArray[i = 1].swordhead);
		XMVECTOR p1Head = XMLoadFloat3(&usedPositionArray[i].swordhead);
		XMVECTOR p2Head = XMLoadFloat3(&usedPositionArray[i + 1].swordhead);
		XMVECTOR p3Head = i == usedPositionArray.size() - 2 ? (p0Head + p2Head) * 0.5f : XMLoadFloat3(&usedPositionArray[i + 2].swordhead);

		XMVECTOR p0Tail = i == 0 ? (XMLoadFloat3(&usedPositionArray[1].swordtail) + XMLoadFloat3(&usedPositionArray[2].swordtail)) * 0.5f : XMLoadFloat3(&usedPositionArray[i - 1].swordtail);
		XMVECTOR p1Tail = XMLoadFloat3(&usedPositionArray[i].swordtail);
		XMVECTOR p2Tail = XMLoadFloat3(&usedPositionArray[i + 1].swordtail);
		XMVECTOR p3Tail = i == usedPositionArray.size() - 2 ? (p0Tail + p2Tail) * 0.5f : XMLoadFloat3(&usedPositionArray[i + 2].swordtail);

		for (size_t j = 0; j < static_cast<size_t>(split - 1); ++j)
		{
			newPosition = PositionBuffer();

			newPosition.isUsed = true;
			XMStoreFloat3(&newPosition.swordhead, XMVectorCatmullRom(p0Head, p1Head, p2Head, p3Head, ratio));
			XMStoreFloat3(&newPosition.swordtail, XMVectorCatmullRom(p0Tail, p1Tail, p2Tail, p3Tail, ratio));

			newPositionArray.push_back(newPosition);
			ratio += amount;
		}
		newPositionArray.push_back(usedPositionArray[i + 1]);
	}
	usedPositionArray = newPositionArray;
}