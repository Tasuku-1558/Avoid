#include "HitChecker.h"
#include "TimeSlow.h"
#include "SoundManager.h"
#include "Player.h"
#include "Meteorite.h"
#include "Evaluation.h"
#include "ScoreEarn.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="inEffect"></param>
HitChecker::HitChecker(EffectManager* const inEffect)
	: hit(false)
	, excellent(false)
	, miss(false)
	, great(false)
	, good(false)
	, decisionFlag(false)
	, RADIUS_EXCELLENT(40.0f)
	, RADIUS_GREAT(150.0f)
	, RADIUS_GOOD(1500.0f)
	, RADIUS_MISS(4.0f)
	, SCORE_DECISION_LINE(150)
	, DECISION_END_LINE(-140)
{
	effectManager = inEffect;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
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
	evaluation->ui = Evaluation::Ui::MISS;

	player->playerState = Player::PlayerState::DAMAGE;
	
	miss = true;
}

/// <summary>
/// excellent����
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::ExcellentDecision(Evaluation* evaluation)
{
	evaluation->ui = Evaluation::Ui::EXCELLENT;

	excellent = true;
	TimeSlow::GetInstance().SetTimeSlow(excellent);
}

/// <summary>
/// great����
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::GreatDecision(Evaluation* evaluation)
{
	evaluation->ui = Evaluation::Ui::GREAT;

	great = true;
	TimeSlow::GetInstance().SetTimeSlow(great);
}

/// <summary>
/// good����
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::GoodDecision(Evaluation* evaluation)
{
	evaluation->ui = Evaluation::Ui::GOOD;

	good = true;
}

/// <summary>
/// �v���C���[��覐΂̓����蔻��
/// </summary>
/// <param name="player"></param>
/// <param name="meteorite"></param>
/// <param name="evaluation"></param>
/// <param name="scoreEarn"></param>
void HitChecker::PlayerAndMeteorite(Player* player, vector<Meteorite*>* meteorite, Evaluation* evaluation, ScoreEarn* scoreEarn)
{
	//覐΂ƏՓ˂��Ă��Ȃ��Ȃ�
	hit = false;

	for (auto itr = meteorite->begin(); itr != meteorite->end(); ++itr)
	{
		//覐΂����胉�C���ɓ������画����J�n����
		if ((*itr)->GetPosition().z <= SCORE_DECISION_LINE)
		{
			//�v���C���[����覐΂̍��W���������l���擾
			VECTOR sub = player->GetPosition() - (*itr)->GetPosition();

			//�v���C���[��覐΂̋������v�Z
			float direction = VSize(sub);

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

			//���肵��
			decisionFlag = true;

			//覐΂�����ŏI���C���ɓ˓����Ă���Ȃ画����I������
			if ((*itr)->GetPosition().z <= DECISION_END_LINE)
			{
				if (excellent)
				{
					excellent = false;
					TimeSlow::GetInstance().SetTimeSlow(excellent);

					scoreEarn->UpdateExcellent();

					//�����G�t�F�N�g���o��
					effectManager->CreateExplosionEffect((*itr)->GetPosition());

					//覐΂�������������SE�����Đ�
					SoundManager::GetInstance().SePlayFlag(SoundManager::EXPLOSION);

					hit = true;
				}

				if (miss)
				{
					scoreEarn->UpdateMiss();
					miss = false;
					hit = true;
				}

				if (great)
				{
					great = false;
					TimeSlow::GetInstance().SetTimeSlow(great);

					scoreEarn->UpdateGreat();

					hit = true;
				}

				if (good)
				{
					scoreEarn->UpdateGood();
					good = false;
					hit = true;
				}

				decisionFlag = false;
			}
		}

	}
}