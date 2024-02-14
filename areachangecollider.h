#pragma once
#include"model.h"
#include"gameobject.h"

class AreaChange : public GameObject
{
private:
	static Model* m_Model;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Scene* scene{};
	class Collider* m_AreaChangeCollider{};
	
	bool m_AreaChangeFlag = false;

	class Fade* m_Fade{};

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetAreaChangeFlag() { return m_AreaChangeFlag; }
	void SetAreaChangeFlag(bool flag) { m_AreaChangeFlag = flag; }
};

