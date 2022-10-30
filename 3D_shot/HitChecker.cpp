#include "HitChecker.h"
#include "Player.h"
#include "MeteoriteManager.h"
#include "Meteorite.h"
#include "Explosion.h"
#include "Evaluation.h"

using namespace std;

const float HitChecker::RADIUS_GOOD		 = 1000.0f;	//good�͈̔�
const float HitChecker::RADIUS_GREAT	 = 250.0f;	//great�͈̔�
const float HitChecker::RADIUS_EXCELLENT = 40.0f;	//excellent�͈̔�
const float HitChecker::RADIUS_MISS		 = 4.0f;	//miss�͈̔�

const int	HitChecker::SCORE_GOOD		 = 100;		//good�̃X�R�A
const int	HitChecker::SCORE_GREAT		 = 200;		//great�̃X�R�A
const int	HitChecker::SCORE_EXCELLENT  = 600;		//excellent�̃X�R�A
const int	HitChecker::SCORE_MISS		 = 300;		//miss�̃X�R�A

const int	HitChecker::FIRST_SCORE		 = 0;		//�X�R�A�̏����l
const int	HitChecker::FIRST_DIRECTION  = 0;		//�����̏����l


HitChecker::HitChecker()
	: score(0)
	, direction(0.0f)
	, hit(false)
{
	//�����Ȃ�
}

HitChecker::~HitChecker()
{
	//�����Ȃ�
}

void HitChecker::Initialize()
{
	score = FIRST_SCORE;
	direction = FIRST_DIRECTION;
}

void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite[]/*vector<Meteorite*> meteorite*/, MeteoriteManager* meteoriteManager, Explosion* explosion,Evaluation* evaluation)
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER;/*meteoriteManager->GetSize();*/ ++i)
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
				score -= SCORE_MISS;

				evaluation->ui = UI::Miss;
			}

			//覐΂ƃM���M���͈̔�
			else if (direction < RADIUS_EXCELLENT + sphereMeteorite.radius)
			{
				score += SCORE_EXCELLENT;
				
				evaluation->ui = UI::Excellent;

				explosion->Update(meteorite[i]);
			}
			
			//覐΂ƒ����炢�͈̔�
			else if (direction < RADIUS_GREAT + sphereMeteorite.radius)
			{
				score += SCORE_GREAT;
				
				evaluation->ui = UI::Great;
			}

			//覐΂ƈ�ԗ���Ă���
			else if (direction < RADIUS_GOOD + sphereMeteorite.radius)
			{
				score += SCORE_GOOD;
				
				evaluation->ui = UI::Good;
			}

			//覐΂ƐڐG�������͔�������
			if (hit)
			{
				//覐΂�����
				meteorite[i] = nullptr;
				delete meteorite[i];
			}
		}
	}
}