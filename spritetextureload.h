#pragma once
#include"gameobject.h"

class	SpriteTextureLoad :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	//���W
	float m_X;
	float m_Y;
	
	//�X�P�[��
	float m_Width;
	float m_Height;

	//�e�N�X�`���̔ԍ�
	int m_TextureCount =0;	

	//�\����\���؂�ւ�
	bool m_Enable = false; 

public:
	void Init(const char* TextureName);
	void Uninit();
	void Update();
	void Draw(float m_X, float m_Y);


	
	void SetTextureScale(float X, float Y) { m_X = X; m_Y = Y; }
	void SetTextureCount(int Count) { m_TextureCount = Count; }
	void SetEnable(bool enable) { m_Enable = enable; }
	int GetCount() { return m_TextureCount; }
};
