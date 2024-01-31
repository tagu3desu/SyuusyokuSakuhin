#pragma once
#include"model.h"
#include"gameobject.h"

//剣の位置を保持する構造体
struct PositionBuffer
{
	XMFLOAT3 swordhead;
	XMFLOAT3 swordtail;
	bool isUsed;
};

//頂点バッファ
struct SwordTrailVertex
{
	XMFLOAT3 position = { 0,0,0 };
	XMFLOAT2 uv = { 0,0 };
};



class SwordTrail : public GameObject
{
private:



	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	std::vector<PositionBuffer> positionArray;	//過去の剣の位置を保存する
	std::vector<SwordTrailVertex> vertex;	//剣の軌跡を表す頂点データを保持する
	PositionBuffer tempPosition;			//現在のフレームでの剣の位置


	D3DXMATRIX m_Parent{};
	int split; //splitをメンバ変数として宣言


public:
	SwordTrail(int bufferSize);				//コンストラクタでposArrayのサイズを決定
	void SetPosition(XMFLOAT3& head, XMFLOAT3& tail);	//履歴を更新して、頂点バッファを更新する
	std::vector<PositionBuffer> GetUsedPositionArray(); //現在フレームの剣の一を保持する
	void CreateCurveVertex(std::vector<PositionBuffer>& usedPositionArray);


	void Init();
	void Uninit();
	void Update();
	void Draw();
};


