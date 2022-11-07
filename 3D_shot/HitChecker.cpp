#include "HitChecker.h"
#include "TimeSlow.h"
#include "Player.h"
#include "Meteorite.h"
#include "Explosion.h"
#include "Evaluation.h"
#include "EarnScore.h"
#include <math.h>


using namespace std;

const float HitChecker::RADIUS_GOOD		 = 1000.0f;	//good�͈̔�
const float HitChecker::RADIUS_GREAT	 = 250.0f;	//great�͈̔�
const float HitChecker::RADIUS_EXCELLENT = 40.0f;	//excellent�͈̔�
const float HitChecker::RADIUS_MISS		 = 4.0f;	//miss�͈̔�


HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, count(0.0f)
	, slow(0.0f)
{
	//�����Ȃ�
}

HitChecker::~HitChecker()
{
	//�����Ȃ�
}

void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite[], Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore)
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; ++i)
	{
		if (meteorite[i] != nullptr && meteorite[i]->GetPosition().z <= 10)
		{
			//�����������ǂ���
			hit = true;
			
			//覐΂̓����蔻�苅���擾
			Math3d::Sphere sphereMeteorite = meteorite[i]->GetCollisionSphere();

			double posX = player->GetPosition().x - meteorite[i]->GetPosition().x;
			double posY = player->GetPosition().y - meteorite[i]->GetPosition().y;
			
			//�v���C���[��覐΂̂Q�_�Ԃ̋������v�Z
			direction = sqrt(pow(posX, 2) + pow(posY, 2));
			
			//覐΂ƏՓ˂�����
			if (direction < RADIUS_MISS + sphereMeteorite.radius)
			{
				earnscore->UpdateMiss();
				
				evaluation->ui = UI::Miss;

				player->state = State::Damage;
			}

			//覐΂ƃM���M���͈̔�
			else if (direction < RADIUS_EXCELLENT + sphereMeteorite.radius)
			{
				
				earnscore->UpdateExcellent();
				
				evaluation->ui = UI::Excellent;
				
				explosion->Update(meteorite[i]);

			}
			
			//覐΂ƒ����炢�͈̔�
			else if (direction < RADIUS_GREAT + sphereMeteorite.radius)
			{
				
				earnscore->UpdateGreat();
				
				evaluation->ui = UI::Great;
			}

			//覐΂ƈ�ԗ���Ă���
			else if (direction < RADIUS_GOOD + sphereMeteorite.radius)
			{
				
				earnscore->UpdateGood();
				
				evaluation->ui = UI::Good;
			}

			//覐΂ƐڐG�������͔�������
			if (hit)
			{
				//覐΂�����
				meteorite[i] = nullptr;
				delete meteorite[i];


				slow = TimeSlow::GetInstance().GetTimeSlow();
				slow -= 100;
			}
		}
	}
}