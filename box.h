#pragma once
#include"model.h"
#include"gameobject.h"

class Box : public GameObject
{
private:
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Scene* scene;
	class Collider* m_BoxCollider{};
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

