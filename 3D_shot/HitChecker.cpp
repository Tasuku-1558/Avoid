#include "Player.h"
#include "Meteorite.h"
#include "HitChecker.h"
#include <math.h>

const float HitChecker::RADIUS_GOOD		 = 30.0f;		//good�͈̔�
const float HitChecker::RADIUS_GREAT	 = 25.0f;		//great�͈̔�
const float HitChecker::RADIUS_EXCELLENT = 20.0f;		//excellent�͈̔�
const float HitChecker::RADIUS_MISS		 =  4.0f;		//miss�͈̔�


HitChecker::HitChecker()
	: Score(0)
	, Direction(0.0f)
	, dis{0}
	, meteoriteHitChecker{0}
{
	/*for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		dis[i] = 100.0f;
		meteoriteHitChecker[i] = { GOOD };
	}*/
}

HitChecker::~HitChecker()
{
	//�����Ȃ�
}


void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite[])
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{

			/*dis[i] = sqrt((player->GetPosition().x - meteorite[i]->GetPosition().x) *
				(player->GetPosition().x - meteorite[i]->GetPosition().x) +
				(player->GetPosition().y - meteorite[i]->GetPosition().x) *
				(player->GetPosition().x - meteorite[i]->GetPosition().y) +
				(player->GetPosition().x - meteorite[i]->GetPosition().z) *
				(player->GetPosition().x - meteorite[i]->GetPosition().z));*/

			double HIT_DIS = 10.0f;
			double EXCELLENT_DIS = 15.0f;

			if (meteorite[i]->GetPosition().z <= 10)
			{
				//�����������ǂ���
				bool Hit = true;
				
				/*if (meteoriteHitChecker[i] != HIT)
				{
					if (dis[i] < HIT_DIS)
					{
						meteoriteHitChecker[i] = HIT;

						Score -= 300;
						printfDx("miss! ");
					}
					else if (dis[i] < EXCELLENT_DIS)
					{
						meteoriteHitChecker[i] = EXCELLENT;

						Score += 600;
						printfDx("excellent! ");
					}
				}*/


				//�v���C���[��覐Η������瓖���蔻�苅���擾
				Math3d::Sphere SpherePlayer = player->GetCollsionSphere();
				Math3d::Sphere SphereMeteorite = meteorite[i]->GetCollisionSphere();

				double a = player->GetPosition().x - meteorite[i]->GetPosition().x;
				double b = player->GetPosition().y - meteorite[i]->GetPosition().y;

				
				//�v���C���[��覐΂̂Q�_�Ԃ̋������v�Z
				Direction = sqrt(pow(a, 2) + pow(b, 2));
				

				//覐΂ƏՓ˂�����
				if (Direction < RADIUS_MISS + SphereMeteorite.Radius)
				{

					Score -= 300;
					
					//�����������m�F�p
					//��ŏ���
					printfDx("miss! ");

				}

				//覐΂ƃM���M���͈̔�
				else if (Direction < RADIUS_EXCELLENT + SphereMeteorite.Radius)
				{

					Score += 600;

					//�����������m�F�p
					//��ŏ���
					printfDx("excellent�I ");

				}

				//覐΂ƒ����炢�͈̔�
				else if (Direction < RADIUS_GREAT + SphereMeteorite.Radius)
				{

					Score += 200;

					//�����������m�F�p
					//��ŏ���
					printfDx("great�I ");
				}

				//覐΂ƈ�ԗ���Ă���
				else if (Direction < RADIUS_GOOD + SphereMeteorite.Radius)
				{
					
					Score += 100;

					//�����������m�F�p
					//��ŏ���
					printfDx("good�I ");
				}

				//覐΂ƐڐG�������͔�������
				if (Hit)
				{
					/*dis[i] = 100.0f;
					meteoriteHitChecker[i] = { GOOD };*/

					//覐΂�����
					delete meteorite[i];
					meteorite[i] = nullptr;
				}
			}
		}
	}
}
