#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"model.h"





class BoxCollider : public Component
{
private:
	class Collider* m_Collider;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetMatirx(D3DXMATRIX matrix);
	void SetPosition(D3DXVECTOR3 position);
	void SetScale(D3DXVECTOR3 scale);
};