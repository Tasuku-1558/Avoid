#include "Player.h"
#include "Meteorite.h"
#include "HitChecker.h"

const float HitChecker::RADIUS_GOOD		 = 25.0f;
const float HitChecker::RADIUS_GREAT	 = 20.0f;
const float HitChecker::RADIUS_EXCELLENT = 15.0f;
const float HitChecker::RADIUS_DEAD		 =  8.0f;

double HitChecker::Direction = 0.0f;

int HitChecker::Score = 0;

bool HitChecker::Hit = false;


HitChecker::HitChecker()
{
	//処理なし
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
			if (meteorite[i]->GetPosition().z <= 10)
			{

				//当たったかどうか
				Hit = false;

				//プレイヤーと隕石両方から当たり判定球を取得
				Math3d::Sphere SpherePlayer = player->GetCollsionSphere();
				Math3d::Sphere SphereMeteorite = meteorite[i]->GetCollisionSphere();

				double a = player->GetPosition().x - meteorite[i]->GetPosition().x;
				double b = player->GetPosition().y - meteorite[i]->GetPosition().y;

				//プレイヤーと隕石の２点間の距離を計算
				Direction = sqrt(pow(a, 2) + pow(b, 2));
				

				//隕石と衝突したら
				if (Direction < RADIUS_DEAD + SphereMeteorite.Radius && !Hit)
				{

					Hit = true;		//当たった

					Score -= 600;

					//当たったか確認用
					//後で消す
					printfDx("miss! ");

				}

				//隕石とギリギリの範囲
				else if (Direction < RADIUS_EXCELLENT + SphereMeteorite.Radius && !Hit)
				{

					Hit = true;		//当たった

					Score += 600;

					//当たったか確認用
					//後で消す
					printfDx("excellent！ ");

				}

				//隕石と中くらいの範囲
				else if (Direction < RADIUS_GREAT + SphereMeteorite.Radius && !Hit)
				{

					Hit = true;		//当たった

					Score += 200;

					//当たったか確認用
					//後で消す
					printfDx("great！ ");
				}

				//隕石と一番離れている
				else if (Direction < RADIUS_GOOD + SphereMeteorite.Radius && !Hit)
				{
					Hit = true;		//当たった

					Score += 100;

					//当たったか確認用
					//後で消す
					printfDx("good！ ");
				}

				//隕石と接触もしくは避けたら
				if (Hit)
				{
					//隕石を消す
					meteorite[i] = nullptr;
					delete meteorite[i];
				}
			}
		}
	}
}
