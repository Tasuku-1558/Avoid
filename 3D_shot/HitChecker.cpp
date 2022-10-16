#include "Player.h"
#include "Meteorite.h"
#include "HitChecker.h"
#include <math.h>

const float HitChecker::RADIUS_GOOD		 = 30.0f;		//goodの範囲
const float HitChecker::RADIUS_GREAT	 = 25.0f;		//greatの範囲
const float HitChecker::RADIUS_EXCELLENT = 10.0f;		//excellentの範囲
const float HitChecker::RADIUS_MISS		 =  4.0f;		//missの範囲


HitChecker::HitChecker()
	: Score(0)
	, Direction(0.0f)
	, dis{0}
	, meteoriteHitChecker{0}
{
	/*for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		dis[i] = 100.0f;
		meteoriteHitChecker[i] = { GOOD };
	}*/
}

HitChecker::~HitChecker()
{
	//処理なし
}


void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite[])
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{

			/*dis[i] = sqrt((player->GetPosition().x - meteorite[i]->GetPosition().x) *
				(player->GetPosition().x - meteorite[i]->GetPosition().x) +
				(player->GetPosition().y - meteorite[i]->GetPosition().x) *
				(player->GetPosition().x - meteorite[i]->GetPosition().y) +
				(player->GetPosition().x - meteorite[i]->GetPosition().z) *
				(player->GetPosition().x - meteorite[i]->GetPosition().z));*/

			double HIT_DIS = 10.0f;
			double EXCELLENT_DIS = 15.0f;

			if (meteorite[i]->GetPosition().z <= 10)
			{
				//当たったかどうか
				bool Hit = true;
				
				/*if (meteoriteHitChecker[i] != HIT)
				{
					if (dis[i] < HIT_DIS)
					{
						meteoriteHitChecker[i] = HIT;

						Score -= 300;
						printfDx("miss! ");
					}
					else if (dis[i] < EXCELLENT_DIS)
					{
						meteoriteHitChecker[i] = EXCELLENT;

						Score += 600;
						printfDx("excellent! ");
					}
				}*/


				//プレイヤーと隕石両方から当たり判定球を取得
				Math3d::Sphere SpherePlayer = player->GetCollsionSphere();
				Math3d::Sphere SphereMeteorite = meteorite[i]->GetCollisionSphere();

				double a = player->GetPosition().x - meteorite[i]->GetPosition().x;
				double b = player->GetPosition().y - meteorite[i]->GetPosition().y;

				
				//プレイヤーと隕石の２点間の距離を計算
				Direction = sqrt(pow(a, 2) + pow(b, 2));
				

				//隕石と衝突したら
				if (Direction < RADIUS_MISS + SphereMeteorite.Radius)
				{

					Score -= 300;
					
					//当たったか確認用
					//後で消す
					printfDx("miss! ");

				}

				//隕石とギリギリの範囲
				else if (Direction < RADIUS_EXCELLENT + SphereMeteorite.Radius)
				{

					Score += 600;

					//当たったか確認用
					//後で消す
					printfDx("excellent！ ");

				}

				//隕石と中くらいの範囲
				else if (Direction < RADIUS_GREAT + SphereMeteorite.Radius)
				{

					Score += 200;

					//当たったか確認用
					//後で消す
					printfDx("great！ ");
				}

				//隕石と一番離れている
				else if (Direction < RADIUS_GOOD + SphereMeteorite.Radius)
				{
					
					Score += 100;

					//当たったか確認用
					//後で消す
					printfDx("good！ ");
				}

				//隕石と接触もしくは避けたら
				if (Hit)
				{
					/*dis[i] = 100.0f;
					meteoriteHitChecker[i] = { GOOD };*/

					//隕石を消す
					delete meteorite[i];
					meteorite[i] = nullptr;
				}
			}
		}
	}
}
