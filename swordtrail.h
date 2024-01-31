#pragma once
#include"model.h"
#include"gameobject.h"

//���̈ʒu��ێ�����\����
struct PositionBuffer
{
	XMFLOAT3 swordhead;
	XMFLOAT3 swordtail;
	bool isUsed;
};

//���_�o�b�t�@
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

	std::vector<PositionBuffer> positionArray;	//�ߋ��̌��̈ʒu��ۑ�����
	std::vector<SwordTrailVertex> vertex;	//���̋O�Ղ�\�����_�f�[�^��ێ�����
	PositionBuffer tempPosition;			//���݂̃t���[���ł̌��̈ʒu


	D3DXMATRIX m_Parent{};
	int split; //split�������o�ϐ��Ƃ��Đ錾


public:
	SwordTrail(int bufferSize);				//�R���X�g���N�^��posArray�̃T�C�Y������
	void SetPosition(XMFLOAT3& head, XMFLOAT3& tail);	//�������X�V���āA���_�o�b�t�@���X�V����
	std::vector<PositionBuffer> GetUsedPositionArray(); //���݃t���[���̌��̈��ێ�����
	void CreateCurveVertex(std::vector<PositionBuffer>& usedPositionArray);


	void Init();
	void Uninit();
	void Update();
	void Draw();
};


