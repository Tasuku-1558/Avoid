#include "HitChecker.h"
#include "Player.h"
#include "Meteorite.h"
#include "ScoreEarn.h"
#include "TimeSlow.h"
#include "SoundManager.h"

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="inEffect">�G�t�F�N�g�}�l�[�W���[�̃|�C���^</param>
/// <param name="inEvaluation">�]��UI�N���X�̃|�C���^</param>
HitChecker::HitChecker(EffectManager* const inEffect, Evaluation* const inEvaluation)
	: distance(0.0f)
	, hit(false)
	, excellent(false)
	, miss(false)
	, great(false)
	, good(false)
	, decisionFlag(false)
	, DECISION_START_LINE(150)
	, DECISION_END_LINE(-140)
	, RADIUS_EXCELLENT(100.0f)
	, RADIUS_GREAT(150.0f)
	, RADIUS_GOOD(1500.0f)
	, RADIUS_MISS(70.0f)
{
	effectManager = inEffect;

	evaluation = inEvaluation;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HitChecker::~HitChecker()
{
	//�����Ȃ�
}

/// <summary>
/// �e�]���̔���
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
void HitChecker::Decision(Player* player)
{
	//���肵�ĂȂ��Ȃ�
	if (!decisionFlag)
	{
		//Miss����
		if (distance <= RADIUS_MISS)
		{
			evaluation->ui = Evaluation::Ui::MISS;

			player->playerState = Player::PlayerState::DAMAGE;

			miss = true;
		}

		//Excellent����
		else if (distance <= RADIUS_EXCELLENT)
		{
			evaluation->ui = Evaluation::Ui::EXCELLENT;

			excellent = true;

			TimeSlow::GetInstance().SetTimeSlow(excellent);
		}

		//Great����
		else if (distance <= RADIUS_GREAT)
		{
			evaluation->ui = Evaluation::Ui::GREAT;

			great = true;

			TimeSlow::GetInstance().SetTimeSlow(great);
		}

		//Good����
		else if (distance <= RADIUS_GOOD)
		{
			evaluation->ui = Evaluation::Ui::GOOD;

			good = true;
		}

		//���肵��
		decisionFlag = true;
	}
}

/// <summary>
/// ����I��
/// </summary>
/// <param name="scoreEarn">�X�R�A�v�Z�̃|�C���^</param>
void HitChecker::DecisionEnd(ScoreEarn* scoreEarn)
{
	if (excellent)
	{
		scoreEarn->ExcellentScore();
		excellent = false;

		TimeSlow::GetInstance().SetTimeSlow(excellent);

		//覐΂�������������SE�����Đ�
		SoundManager::GetInstance().SePlayFlag(SoundManager::EXPLOSION);
	}

	if (miss)
	{
		scoreEarn->MissScore();
		miss = false;
	}

	if (great)
	{
		scoreEarn->GreatScore();
		great = false;

		TimeSlow::GetInstance().SetTimeSlow(great);
	}

	if (good)
	{
		scoreEarn->GoodScore();
		good = false;
	}

	hit = true;

	decisionFlag = false;
}

/// <summary>
/// �v���C���[��覐΂̏Փ˔���
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
/// <param name="meteorite">覐΂̃|�C���^</param>
/// <param name="scoreEarn">�X�R�A�v�Z�̃|�C���^</param>
void HitChecker::PlayerAndMeteorite(Player* player, vector<Meteorite*>* meteorite, ScoreEarn* scoreEarn)
{
	//覐΂ƏՓ˂��Ă��Ȃ�
	hit = false;

	for (auto itr = meteorite->begin(); itr != meteorite->end(); ++itr)
	{
		//覐΂����胉�C���ɓ������画����J�n����
		if ((*itr)->GetPosition().z <= DECISION_START_LINE)
		{
			//�v���C���[����覐΂̍��W���������l���擾
			VECTOR sub = player->GetPosition() - (*itr)->GetPosition();

			//�v���C���[��覐΂̋������v�Z
			distance = VSize(sub);

			Decision(player);
		}

		//覐΂�����ŏI���C���ɓ˓����Ă���Ȃ画����I������
		if ((*itr)->GetPosition().z <= DECISION_END_LINE)
		{
			if (excellent)
			{
				//�����G�t�F�N�g���o��
				effectManager->CreateEffect((*itr)->GetPosition(), EffectManager::EXPLOSION);
			}
			else
			{
				//���G�t�F�N�g���o��
				effectManager->CreateEffect((*itr)->GetPosition(), EffectManager::FIRE);
			}
			
			DecisionEnd(scoreEarn);
		}
	}
}