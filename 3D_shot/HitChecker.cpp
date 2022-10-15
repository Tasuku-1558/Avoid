#include "Player.h"
#include "Meteorite.h"
#include "HitChecker.h"

const float HitChecker::RADIUS_GOOD		 = 20.0f;
const float HitChecker::RADIUS_GREAT	 = 15.0f;
const float HitChecker::RADIUS_EXCELLENT = 10.0f;
const float HitChecker::RADIUS_DEAD		 =  4.0f;

double HitChecker::Direction = 0.0f;

int HitChecker::Score = 0;


HitChecker::HitChecker()
{
	//�����Ȃ�
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
			if (meteorite[i]->GetPosition().z <= 10)
			{

				//�����������ǂ���
				bool Hit = false;
				
				
				//�v���C���[��覐Η������瓖���蔻�苅���擾
				Math3d::Sphere SpherePlayer = player->GetCollsionSphere();
				Math3d::Sphere SphereMeteorite = meteorite[i]->GetCollisionSphere();

				double a = player->GetPosition().x - meteorite[i]->GetPosition().x;
				double b = player->GetPosition().y - meteorite[i]->GetPosition().y;

				//�v���C���[��覐΂̂Q�_�Ԃ̋������v�Z
				Direction = sqrt(pow(a, 2) + pow(b, 2));
				

				//覐΂ƏՓ˂�����
				if (Direction < RADIUS_DEAD + SphereMeteorite.Radius && !Hit)
				{

					Hit = true;		//��������

					Score -= 600;

					//�����������m�F�p
					//��ŏ���
					printfDx("miss! ");

				}

				//覐΂ƃM���M���͈̔�
				else if (Direction < RADIUS_EXCELLENT + SphereMeteorite.Radius && !Hit)
				{

					Hit = true;		//��������

					Score += 600;

					

					//�����������m�F�p
					//��ŏ���
					printfDx("excellent�I ");

				}

				//覐΂ƒ����炢�͈̔�
				else if (Direction < RADIUS_GREAT + SphereMeteorite.Radius && !Hit)
				{

					Hit = true;		//��������

					Score += 200;

					//�����������m�F�p
					//��ŏ���
					printfDx("great�I ");
				}

				//覐΂ƈ�ԗ���Ă���
				else if (Direction < RADIUS_GOOD + SphereMeteorite.Radius && !Hit)
				{
					Hit = true;		//��������

					Score += 100;

					//�����������m�F�p
					//��ŏ���
					printfDx("good�I ");
				}

				//覐΂ƐڐG�������͔�������
				if (Hit)
				{
					//覐΂�����
					meteorite[i] = nullptr;
					delete meteorite[i];
				}
			}
		}
	}
}
