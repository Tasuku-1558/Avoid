#include "HitChecker.h"
#include "TimeSlow.h"
#include "Player.h"
#include "Meteorite.h"
#include "Explosion.h"
#include "Evaluation.h"
#include "ScoreEarn.h"
//#include <math.h>

using namespace Math3d;

const float HitChecker::RADIUS_GOOD			= 1500.0f;	//goodの範囲
const float HitChecker::RADIUS_GREAT		= 150.0f;	//greatの範囲
const float HitChecker::RADIUS_EXCELLENT	= 40.0f;	//excellentの範囲
const float HitChecker::RADIUS_MISS			= 4.0f;		//missの範囲
const int   HitChecker::SCORE_DECISION_LINE = 150;		//スコア判定ライン
const int   HitChecker::DECISION_END_LINE	= -140;		//判定終了ライン


HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, excellent(false)
	, miss(false)
	, great(false)
	, good(false)
	, decisionFlag(false)
{
	//処理なし
}

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
	evaluation->ui = UI::MISS;

	player->state = State::DAMAGE;
	
	miss = true;
}

/// <summary>
/// excellent判定
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::ExcellentDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::EXCELLENT;

	excellent = true;
	TimeSlow::GetInstance().SetTimeSlow(excellent);
}

/// <summary>
/// great判定
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::GreatDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::GREAT;

	great = true;
	TimeSlow::GetInstance().SetTimeSlow(great);
}

/// <summary>
/// good判定
/// </summary>
/// <param name="evaluation"></param>
void HitChecker::GoodDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::GOOD;

	good = true;
	
}

/// <summary>
/// プレイヤーと隕石の当たり判定
/// </summary>
/// <param name="player"></param>
/// <param name="meteorite"></param>
/// <param name="explosion"></param>
/// <param name="evaluation"></param>
/// <param name="scoreearn"></param>
void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite, Explosion* explosion, Evaluation* evaluation, ScoreEarn* scoreearn)
{
	
	hit = false;	//隕石と衝突していないなら

	//隕石が判定ラインに入ったら判定を開始する
	if (meteorite->GetPosition().z <= SCORE_DECISION_LINE)
	{

		//プレイヤーから隕石の座標を引いた値を取得
		VECTOR sub = player->GetPosition() - meteorite->GetPosition();

		//プレイヤーと隕石の2点間の距離を計算
		float direction = sqrt(pow(sub.x, 2) + pow(sub.y, 2));

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

		decisionFlag = true;				// 判定した

		//隕石が判定最終ラインに突入しているなら判定を終了する
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