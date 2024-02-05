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
	void Update(D3DXMATRIX matrix);
	void Draw();
};