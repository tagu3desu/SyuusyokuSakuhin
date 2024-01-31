#pragma once
#include"model.h"
#include"gameobject.h"

class Child : public GameObject
{
private:
	//class Model* m_Model{};
	static Model* m_Model;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Player* m_Parent;
public:
	static void Load();
	static void Unload();


	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetParent(Player* Parent) { m_Parent = Parent;}
};