#pragma once
#include"model.h"
#include"gameobject.h"

class RockEffect : public GameObject
{
private:
	static Model* m_Model;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Scene* scene{};
	class BoxCollider* m_RockCollider{};

	
	
public:
	static void Load();
	static void Unload();

	

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

