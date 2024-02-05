#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"model.h"
#include"boxcollider.h"
#include"collider.h"



void BoxCollider::Init()
{
	m_Collider = new Collider();
	m_Collider->Init();
};

void BoxCollider::Uninit()
{
	m_Collider->Uninit();
	delete m_Collider;
}

void BoxCollider::Update(D3DXMATRIX matrix)
{
	m_Collider->SetMatrix(matrix);
}

void BoxCollider::Draw()
{
	m_Collider->Draw();
}


