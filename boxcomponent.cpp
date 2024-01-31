#include "boxcomponent.h"
#include "manager.h"
#include "scene.h"

void BoxComponent::Init()
{
	
	collider = Manager::GetScene()->AddGameObject<BoxCollider>(COLLIDER_LAYER);
	
	collider->SetScale(D3DXVECTOR3(30.0f, 30.0f, 30.0f));
}

void BoxComponent::Uninit()
{

}
void BoxComponent::Update()
{
	//collider->SetScale(D3DXVECTOR3(size, size, size) * scaleoffset);
}

void BoxComponent::Draw()
{
}
