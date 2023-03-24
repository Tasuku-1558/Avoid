#include "HitChecker.h"
#include "TimeSlow.h"
#include "SoundManager.h"
#include "Player.h"
#include "Meteorite.h"
#include "Evaluation.h"
#include "ScoreEarn.h"


using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
HitChecker::~HitChecker()
{
	//処理なし
}

/// <summary>
/// miss判定
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
/// excellent判定
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::ExcellentDecision(Evaluation* evaluation)
{
	evaluation->ui = Evaluation::Ui::EXCELLENT;

	excellent = true;
	TimeSlow::GetInstance().SetTimeSlow(excellent);
}

/// <summary>
/// great判定
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::GreatDecision(Evaluation* evaluation)
{
	evaluation->ui = Evaluation::Ui::GREAT;

	great = true;
	TimeSlow::GetInstance().SetTimeSlow(great);
}

/// <summary>
/// good判定
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::GoodDecision(Evaluation* evaluation)
{
	evaluation->ui = Evaluation::Ui::GOOD;

	good = true;
}

/// <summary>
/// プレイヤーと隕石の当たり判定
/// </summary>
/// <param name="player"></param>
/// <param name="meteorite"></param>
/// <param name="evaluation"></param>
/// <param name="scoreEarn"></param>
void HitChecker::PlayerAndMeteorite(Player* player, vector<Meteorite*>* meteorite, Evaluation* evaluation, ScoreEarn* scoreEarn)
{
	//隕石と衝突していないなら
	hit = false;

	for (auto itr = meteorite->begin(); itr != meteorite->end(); ++itr)
	{
		//隕石が判定ラインに入ったら判定を開始する
		if ((*itr)->GetPosition().z <= SCORE_DECISION_LINE)
		{
			//プレイヤーから隕石の座標を引いた値を取得
			VECTOR sub = player->GetPosition() - (*itr)->GetPosition();

			//プレイヤーと隕石の距離を計算
			float direction = VSize(sub);

			//判定してないなら
			if (!decisionFlag)
			{
				//隕石と衝突したら
				if (direction < RADIUS_MISS)
				{
					MissDecision(evaluation, player);
				}

				//隕石とギリギリの範囲
				else if (direction < RADIUS_EXCELLENT)
				{
					ExcellentDecision(evaluation);
				}

				//隕石と中くらいの範囲
				else if (direction < RADIUS_GREAT)
				{
					GreatDecision(evaluation);
				}

				//隕石と一番離れている
				else if (direction < RADIUS_GOOD)
				{
					GoodDecision(evaluation);
				}
			}

			//判定した
			decisionFlag = true;

			//隕石が判定最終ラインに突入しているなら判定を終了する
			if ((*itr)->GetPosition().z <= DECISION_END_LINE)
			{
				if (excellent)
				{
					excellent = false;
					TimeSlow::GetInstance().SetTimeSlow(excellent);

					scoreEarn->UpdateExcellent();

					//爆発エフェクトを出す
					effectManager->CreateExplosionEffect((*itr)->GetPosition());

					//隕石が爆発した時のSE音を再生
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