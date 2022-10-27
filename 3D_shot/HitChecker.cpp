#include "Player.h"
#include "MeteoriteManager.h"
#include "Meteorite.h"
#include "HitChecker.h"
#include "LargeExplosion.h"


const float HitChecker::RADIUS_GOOD		 = 700.0f;	//goodの範囲
const float HitChecker::RADIUS_GREAT	 = 500.0f;	//greatの範囲
const float HitChecker::RADIUS_EXCELLENT = 40.0f;	//excellentの範囲
const float HitChecker::RADIUS_MISS		 = 4.0f;	//missの範囲

const int	HitChecker::SCORE_GOOD		 = 100;		//goodのスコア
const int	HitChecker::SCORE_GREAT		 = 200;		//greatのスコア
const int	HitChecker::SCORE_EXCELLENT  = 600;		//excellentのスコア
const int	HitChecker::SCORE_MISS		 = 300;		//missのスコア

const int	HitChecker::FIRST_SCORE		 = 0;		//スコアの初期値
const int	HitChecker::FIRST_DIRECTION  = 0;		//距離の初期値


HitChecker::HitChecker()
	: score(0)
	, direction(0.0f)
	, hit(false)
	, excellentGraph(0)
	, excellentF(false)
{
	//処理なし
}

HitChecker::~HitChecker()
{
	//処理なし
}

void HitChecker::Initialize()
{
	score = FIRST_SCORE;
	direction = FIRST_DIRECTION;

	excellentGraph = LoadGraph("data/Image/ExcellentEffect.png");
}

void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite[], MeteoriteManager* meteoriteManager, LargeExplosion* largeexplosion)
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER/*meteoriteManager->GetSize()*/; ++i)
	{
		if (meteorite[i] != nullptr)
		{
			if (meteorite[i]->GetPosition().z <= 10)
			{
				//当たったかどうか
				hit = true;
				
				
				//隕石の当たり判定球を取得
				Math3d::Sphere sphereMeteorite = meteorite[i]->GetCollisionSphere();

				double posX = player->GetPosition().x - meteorite[i]->GetPosition().x;
				double posY = player->GetPosition().y - meteorite[i]->GetPosition().y;
				
				//プレイヤーと隕石の２点間の距離を計算
				direction = sqrt(pow(posX, 2) + pow(posY, 2));
				

				//隕石と衝突したら
				if (direction < RADIUS_MISS + sphereMeteorite.radius)
				{
					excellentF = true;
					score -= SCORE_MISS;

					player->state = State::Miss;
					
					//当たったか確認用
					//後で消す
					printfDx("miss! ");

				}

				//隕石とギリギリの範囲
				else if (direction < RADIUS_EXCELLENT + sphereMeteorite.radius)
				{
					
					score += SCORE_EXCELLENT;

					largeexplosion->Update(meteorite[i]);

					

					//当たったか確認用
					//後で消す
					printfDx("excellent！ ");

				}

				//隕石と中くらいの範囲
				else if (direction < RADIUS_GREAT + sphereMeteorite.radius)
				{
					
					score += SCORE_GREAT;

					//当たったか確認用
					//後で消す
					printfDx("great！ ");
				}

				//隕石と一番離れている
				else if (direction < RADIUS_GOOD + sphereMeteorite.radius)
				{
					
					score += SCORE_GOOD;

					//当たったか確認用
					//後で消す
					printfDx("good！ ");
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

void HitChecker::Draw()
{
	if (excellentF)
	{
		DrawGraph(800, 50, excellentGraph, TRUE);
		count += 1.0f;

		if (count < 10.0f)
		{
			excellentF = false;
			count = 0.0f;
		}
	}
}