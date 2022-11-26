#include "HitChecker.h"
#include "TimeSlow.h"
#include "Player.h"
#include "Meteorite.h"
#include "Explosion.h"
#include "Evaluation.h"
#include "EarnScore.h"
#include <math.h>

using namespace std;

const float HitChecker::RADIUS_GOOD			= 1000.0f;	//good�͈̔�
const float HitChecker::RADIUS_GREAT		= 250.0f;	//great�͈̔�
const float HitChecker::RADIUS_EXCELLENT	= 40.0f;	//excellent�͈̔�
const float HitChecker::RADIUS_MISS			= 4.0f;		//miss�͈̔�
const int   HitChecker::SCORE_DECISION_LINE = 150;		//�X�R�A���胉�C��
const int   HitChecker::DECISION_END_LINE	= -140;		//����I�����C��


HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, excellent(false)
	, miss(false)
	, great(false)
	, good(false)
	, decisionFlag(false)
{
	//�����Ȃ�
}

HitChecker::~HitChecker()
{
	//�����Ȃ�
}

//miss����
void HitChecker::MissDecision(Evaluation* evaluation, Player* player)
{
	evaluation->ui = UI::Miss;

	player->state = State::Damage;
	
	miss = true;
}

//excellent����
void HitChecker::ExcellentDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::Excellent;

	excellent = true;
	TimeSlow::GetInstance().SetTimeSlow(excellent);
}

//great����
void HitChecker::GreatDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::Great;

	great = true;
	TimeSlow::GetInstance().SetTimeSlow(great);
}

//good����
void HitChecker::GoodDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::Good;

	good = true;
	
}

//�v���C���[��覐΂̓����蔻��
void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite[], Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore)
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; ++i)
	{
		//覐΂����݂��Ă��Ċ����胉�C���ɓ������画����J�n����
		if (meteorite[i] != nullptr && meteorite[i]->GetPosition().z <= SCORE_DECISION_LINE)
		{
			//覐΂̓����蔻�苅���擾
			Math3d::Sphere sphereMeteorite = meteorite[i]->GetCollisionSphere();

			//�v���C���[����覐΂̍��W���������l���擾
			double posX = player->GetPosition().x - meteorite[i]->GetPosition().x;
			double posY = player->GetPosition().y - meteorite[i]->GetPosition().y;

			//�v���C���[��覐΂̂Q�_�Ԃ̋������v�Z
			direction = sqrt(pow(posX, 2) + pow(posY, 2));
			
			//���肵�ĂȂ��Ȃ�
			if (!decisionFlag)
			{
				
				//覐΂ƏՓ˂�����
				if (direction < RADIUS_MISS + sphereMeteorite.radius)
				{
					MissDecision(evaluation, player);
				}

				//覐΂ƃM���M���͈̔�
				else if (direction < RADIUS_EXCELLENT + sphereMeteorite.radius)
				{
					ExcellentDecision(evaluation);
				}

				//覐΂ƒ����炢�͈̔�
				else if (direction < RADIUS_GREAT + sphereMeteorite.radius)
				{
					GreatDecision(evaluation);
				}

				//覐΂ƈ�ԗ���Ă���
				else if (direction < RADIUS_GOOD + sphereMeteorite.radius)
				{
					GoodDecision(evaluation);
				}
			}

			decisionFlag = true;							// ���肵��

			//覐΂�����ŏI���C���ɓ˓����Ă���Ȃ画����I������
			if (meteorite[i]->GetPosition().z <= DECISION_END_LINE)
			{
				if (excellent)
				{
					excellent = false;
					TimeSlow::GetInstance().SetTimeSlow(excellent);
					

					earnscore->UpdateExcellent();
					explosion->Update(meteorite[i]);
					
					hit = true;
				}

				if (miss)
				{
					earnscore->UpdateMiss();
					miss = false;
					hit = true;
				}

				if (great)
				{
					great = false;
					TimeSlow::GetInstance().SetTimeSlow(great);
					
					earnscore->UpdateGreat();

					hit = true;
				}

				if (good)
				{
					earnscore->UpdateGood();
					good = false;
					hit = true;
				}

				//覐΂ƐڐG�������͔�������
				if (hit)
				{
					//覐΂�����
					meteorite[i] = nullptr;
					delete meteorite[i];
				}

				decisionFlag = false;
			}
		}
	}
}