#include "HitChecker.h"
#include "TimeSlow.h"
#include "Player.h"
#include "Meteorite.h"
#include "Explosion.h"
#include "Evaluation.h"
#include "ScoreEarn.h"
#include <math.h>

using namespace std;

const float HitChecker::RADIUS_GOOD			= 1500.0f;	//good�͈̔�
const float HitChecker::RADIUS_GREAT		= 150.0f;	//great�͈̔�
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

/// <summary>
/// miss����
/// </summary>
/// <param name="evaluation"></param>
/// <param name="player"></param>
void HitChecker::MissDecision(Evaluation* evaluation, Player* player)
{
	evaluation->ui = UI::MISS;

	player->state = State::DAMAGE;
	
	miss = true;
}

/// <summary>
/// excellent����
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::ExcellentDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::EXCELLENT;

	excellent = true;
	TimeSlow::GetInstance().SetTimeSlow(excellent);
}

/// <summary>
/// great����
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::GreatDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::GREAT;

	great = true;
	TimeSlow::GetInstance().SetTimeSlow(great);
}

/// <summary>
/// good����
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::GoodDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::GOOD;

	good = true;
	
}

/// <summary>
/// �v���C���[��覐΂̓����蔻��
/// </summary>
/// <param name="player"></param>
/// <param name="meteorite"></param>
/// <param name="explosion"></param>
/// <param name="evaluation"></param>
/// <param name="scoreearn"></param>
void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite, Explosion* explosion, Evaluation* evaluation, ScoreEarn* scoreearn)
{
	
	hit = false;	//覐΂ƏՓ˂��Ă��Ȃ��Ȃ�

	//覐΂����胉�C���ɓ������画����J�n����
	if (meteorite->GetPosition().z <= SCORE_DECISION_LINE)
	{

		//�v���C���[����覐΂̍��W���������l���擾
		double posX = player->GetPosition().x - meteorite->GetPosition().x;
		double posY = player->GetPosition().y - meteorite->GetPosition().y;

		//�v���C���[��覐΂̂Q�_�Ԃ̋������v�Z
		direction = sqrt(pow(posX, 2) + pow(posY, 2));

		//���肵�ĂȂ��Ȃ�
		if (!decisionFlag)
		{
			//覐΂ƏՓ˂�����
			if (direction < RADIUS_MISS)
			{
				MissDecision(evaluation, player);
			}

			//覐΂ƃM���M���͈̔�
			else if (direction < RADIUS_EXCELLENT)
			{
				ExcellentDecision(evaluation);
			}

			//覐΂ƒ����炢�͈̔�
			else if (direction < RADIUS_GREAT)
			{
				GreatDecision(evaluation);
			}

			//覐΂ƈ�ԗ���Ă���
			else if (direction < RADIUS_GOOD)
			{
				GoodDecision(evaluation);
			}
		}

		decisionFlag = true;				// ���肵��

		//覐΂�����ŏI���C���ɓ˓����Ă���Ȃ画����I������
		if (meteorite->GetPosition().z <= DECISION_END_LINE)
		{
			if (excellent)
			{
				excellent = false;
				TimeSlow::GetInstance().SetTimeSlow(excellent);

				scoreearn->UpdateExcellent();
				explosion->Update(meteorite);

				hit = true;
			}

			if (miss)
			{
				scoreearn->UpdateMiss();
				miss = false;
				hit = true;
			}

			if (great)
			{
				great = false;
				TimeSlow::GetInstance().SetTimeSlow(great);

				scoreearn->UpdateGreat();

				hit = true;
			}

			if (good)
			{
				scoreearn->UpdateGood();
				good = false;
				hit = true;
			}

			decisionFlag = false;
		}
	}
}