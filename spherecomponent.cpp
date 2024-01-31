#include "spherecomponent.h"
#include "manager.h"
#include "scene.h"

void SphereComponent::Init()
{
	
	collider = Manager::GetScene()->AddGameObject<SphereCollider>(COLLIDER_LAYER);
	
	collider->SetScale(D3DXVECTOR3(30.0f, 30.0f, 30.0f));
}

void SphereComponent::Uninit()
{

}
void SphereComponent::Update()
{
	//collider->SetScale(D3DXVECTOR3(size, size, size) * scaleoffset);
}

void SphereComponent::Draw()
{
}
