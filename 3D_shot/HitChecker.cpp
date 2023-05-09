#include "HitChecker.h"
#include "Player.h"
#include "Meteorite.h"
#include "ScoreEarn.h"
#include "TimeSlow.h"
#include "SoundManager.h"

using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="inEffect">エフェクトマネージャーのポインタ</param>
/// <param name="inEvaluation">評価Uiクラスのポインタ</param>
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
/// デストラクタ
/// </summary>
HitChecker::~HitChecker()
{
	//処理なし
}

/// <summary>
/// 各評価の判定
/// </summary>
/// <param name="player">プレイヤーのポインタ</param>
void HitChecker::Decision(Player* player)
{
	//判定してないなら
	if (!decisionFlag)
	{
		//Miss判定
		if (distance <= RADIUS_MISS)
		{
			evaluation->ui = Evaluation::Ui::MISS;

			player->playerState = Player::PlayerState::DAMAGE;

			miss = true;
		}

		//Excellent判定
		else if (distance <= RADIUS_EXCELLENT)
		{
			evaluation->ui = Evaluation::Ui::EXCELLENT;

			excellent = true;

			TimeSlow::GetInstance().SetTimeSlow(excellent);
		}

		//Great判定
		else if (distance <= RADIUS_GREAT)
		{
			evaluation->ui = Evaluation::Ui::GREAT;

			great = true;

			TimeSlow::GetInstance().SetTimeSlow(great);
		}

		//Good判定
		else if (distance <= RADIUS_GOOD)
		{
			evaluation->ui = Evaluation::Ui::GOOD;

			good = true;
		}

		//判定した
		decisionFlag = true;
	}
}

/// <summary>
/// 判定終了
/// </summary>
/// <param name="scoreEarn">スコア計算のポインタ</param>
void HitChecker::DecisionEnd(ScoreEarn* scoreEarn)
{
	if (excellent)
	{
		scoreEarn->ExcellentScore();
		excellent = false;

		TimeSlow::GetInstance().SetTimeSlow(excellent);

		//隕石が爆発した時のSE音を再生
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
/// プレイヤーと隕石の衝突判定
/// </summary>
/// <param name="playerPosition">プレイヤーの座標</param>
/// <param name="player">プレイヤーのポインタ</param>
/// <param name="meteorite">隕石のポインタ</param>
/// <param name="scoreEarn">スコア計算のポインタ</param>
void HitChecker::PlayerAndMeteorite(VECTOR playerPosition, Player* player, vector<Meteorite*>* meteorite, ScoreEarn* scoreEarn)
{
	//隕石と衝突していない
	hit = false;

	for (auto itr = meteorite->begin(); itr != meteorite->end(); ++itr)
	{
		//隕石が判定ラインに入ったら判定を開始する
		if ((*itr)->GetPosition().z <= DECISION_START_LINE)
		{
			//プレイヤーから隕石の座標を引いた値を取得
			VECTOR sub = playerPosition - (*itr)->GetPosition();

			//プレイヤーと隕石の距離を計算
			distance = VSize(sub);

			Decision(player);
		}

		//隕石が判定最終ラインに突入しているなら判定を終了する
		if ((*itr)->GetPosition().z <= DECISION_END_LINE)
		{
			if (excellent)
			{
				//爆発エフェクトを出す
				effectManager->CreateEffect((*itr)->GetPosition(), EffectManager::EXPLOSION);
			}
			else
			{
				//炎エフェクトを出す
				effectManager->CreateEffect((*itr)->GetPosition(), EffectManager::FIRE);
			}
			
			DecisionEnd(scoreEarn);
		}
	}
}