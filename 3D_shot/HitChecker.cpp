#include "HitChecker.h"
#include "TimeSlow.h"
#include "Player.h"
#include "Meteorite.h"
#include "Explosion.h"
#include "Evaluation.h"
#include "EarnScore.h"
#include <math.h>

using namespace std;

const float HitChecker::RADIUS_GOOD		 = 1000.0f;	//goodの範囲
const float HitChecker::RADIUS_GREAT	 = 250.0f;	//greatの範囲
const float HitChecker::RADIUS_EXCELLENT = 40.0f;	//excellentの範囲
const float HitChecker::RADIUS_MISS		 = 4.0f;	//missの範囲


HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, slow(false)
	, miss(false)
	, great(false)
	, good(false)
	, a(false)
{
	//処理なし
}

HitChecker::~HitChecker()
{
	//処理なし
}

//miss判定
void HitChecker::MissDecision(Evaluation* evaluation, Player* player)
{
	evaluation->ui = UI::Miss;

	player->state = State::Damage;
	a = false;
	miss = true;
}

//excellent判定
void HitChecker::ExcellentDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::Excellent;

	slow = true;
	TimeSlow::GetInstance().SetTimeSlow(slow);
	a = false;
}

//great判定
void HitChecker::GreatDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::Great;

	great = true;
	TimeSlow::GetInstance().SetTimeSlow(great);
	a = false;
}

//good判定
void HitChecker::GoodDecision(Evaluation* evaluation)
{
	evaluation->ui = UI::Good;

	good = true;
	a = false;
}

//プレイヤーと隕石の当たり判定
void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite[], Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore)
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; ++i)
	{
		if (meteorite[i] != nullptr && meteorite[i]->GetPosition().z <= 150)
		{
			a = true;
			//隕石の当たり判定球を取得
			Math3d::Sphere sphereMeteorite = meteorite[i]->GetCollisionSphere();

			//プレイヤーから隕石の座標を引いた値を取得
			double posX = player->GetPosition().x - meteorite[i]->GetPosition().x;
			double posY = player->GetPosition().y - meteorite[i]->GetPosition().y;

			//プレイヤーと隕石の２点間の距離を計算
			direction = sqrt(pow(posX, 2) + pow(posY, 2));
			
			if (a)
			{

				a = false;
				//隕石と衝突したら
				if (direction < RADIUS_MISS + sphereMeteorite.radius)
				{
					MissDecision(evaluation, player);
				}

				//隕石とギリギリの範囲
				else if (direction < RADIUS_EXCELLENT + sphereMeteorite.radius)
				{
					ExcellentDecision(evaluation);
				}

				//隕石と中くらいの範囲
				else if (direction < RADIUS_GREAT + sphereMeteorite.radius)
				{
					GreatDecision(evaluation);
				}

				//隕石と一番離れている
				else if (direction < RADIUS_GOOD + sphereMeteorite.radius)
				{
					GoodDecision(evaluation);
				}
			}
			if (meteorite[i]->GetPosition().z <= -140)
			{
				if (slow)
				{
					
					slow = false;
					TimeSlow::GetInstance().SetTimeSlow(slow);
					
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

				//隕石と接触もしくは避けたら
				if (hit)
				{
					//隕石を消す
					meteorite[i] = nullptr;
					delete meteorite[i];
				}
			}
		}
	}
}