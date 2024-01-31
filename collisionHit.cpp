#include"main.h"
#include"manager.h"
#include"scene.h"
#include"collisionHit.h"
#include"spherecomponent.h"
#include"bullet.h"
#include"box.h"
#include"player.h"
#include"explosion.h"
#include"enemy.h"
#include<chrono>
bool CollisionHit::m_hit;
std::chrono::high_resolution_clock::time_point lastCollisionTime;

void CollisionHit::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	std::vector<Enemy*> enemies = scene->GetGameObjects<Enemy>();

	

	for (GameObject* obj1:scene->GetList(COLLIDER_LAYER)) {
		for (GameObject* obj2 : scene->GetList(COLLIDER_LAYER)) {
			if (obj1 != obj2)//�����I�u�W�F�N�g����Ȃ����m�F
			{
				SphereCollider* gameObject1 = (SphereCollider*)obj1;
				SphereCollider* gameObject2 = (SphereCollider*)obj2;
				D3DXVECTOR3 distance;
				distance = gameObject1->GlobalPosition - gameObject2->GlobalPosition;
				float length = D3DXVec3Length(&distance);
				for (Enemy* enemy : enemies)
				{
					D3DXVECTOR3 enemyPos = enemy->GetPosition();
					if (length < gameObject1->m_collisionSize + gameObject2->m_collisionSize && player->GetPlayerAttack() && !m_hit)
					{
						m_hit = true;

						Explosion* explosion = scene->AddGameObject<Explosion>();
						explosion->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
						explosion->SetPosition(enemyPos);
						//// �Փ˔����������L�^
						//lastCollisionTime = std::chrono::high_resolution_clock::now();

							////OnCollision�p�̏���
							//float sabun = gameObject1->m_collisionSize + gameObject2->m_collisionSize - length;
							////�������Ƃ�
							//D3DXVECTOR3 vector = gameObject1->GlobalPosition - gameObject2->GlobalPosition;
							////normalize
							//D3DXVec3Normalize(&vector, &vector);
							////�����o���ʂ�e�̍��W�ɂ�����
							//D3DXVECTOR3	setPosition = gameObject1->GetPosition() +  (sabun * vector);
							//gameObject1->SetPosition(setPosition);
							//return;
						return;
					}
					else
					{
						m_hit = false;
					}
				}
				
			}
			
		}
	}
	/*auto currentTime = std::chrono::high_resolution_clock::now();
	auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastCollisionTime).count();

	if (m_hit && elapsedSeconds >= 3) {
		m_hit = false;
	}*/

	//����̏���
	ImGui::Begin("ColliderHit");
	ImGui::Checkbox("Hit", &m_hit);
	ImGui::End();
}

