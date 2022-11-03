#include "HitChecker.h"
#include "Player.h"
#include "MeteoriteManager.h"
#include "Meteorite.h"
#include "Explosion.h"
#include "Evaluation.h"
#include "EarnScore.h"

using namespace std;

const float HitChecker::RADIUS_GOOD		 = 1000.0f;	//goodの範囲
const float HitChecker::RADIUS_GREAT	 = 250.0f;	//greatの範囲
const float HitChecker::RADIUS_EXCELLENT = 40.0f;	//excellentの範囲
const float HitChecker::RADIUS_MISS		 = 4.0f;	//missの範囲


HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
{
	//処理なし
}

HitChecker::~HitChecker()
{
	//処理なし
}

void HitChecker::PlayerAndMeteorite(Player* player, /*Meteorite* meteorite[]*/Meteorite* meteorite, MeteoriteManager* meteoriteManager, Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore)
{
	for (int i = 0; i < /*Meteorite::METEORITE_ARRAY_NUMBER;*/meteoriteManager->GetSize(); ++i)
	{
		if (meteorite/*[i] */!= nullptr && meteorite/*[i]*/->GetPosition().z <= 10)
		{
			//当たったかどうか
			hit = true;
			
			//隕石の当たり判定球を取得
			Math3d::Sphere sphereMeteorite = meteorite/*[i]*/->GetCollisionSphere();

			double posX = player->GetPosition().x - meteorite/*[i]*/->GetPosition().x;
			double posY = player->GetPosition().y - meteorite/*[i]*/->GetPosition().y;
			
			//プレイヤーと隕石の２点間の距離を計算
			direction = sqrt(pow(posX, 2) + pow(posY, 2));
			

			//隕石と衝突したら
			if (direction < RADIUS_MISS + sphereMeteorite.radius)
			{
				
				earnscore->UpdateMiss();
				
				evaluation->ui = UI::Miss;
			}

			//隕石とギリギリの範囲
			else if (direction < RADIUS_EXCELLENT + sphereMeteorite.radius)
			{
				
				earnscore->UpdateExcellent();
				
				evaluation->ui = UI::Excellent;

				explosion->Update(meteorite/*[i]*/);
			}
			
			//隕石と中くらいの範囲
			else if (direction < RADIUS_GREAT + sphereMeteorite.radius)
			{
				
				earnscore->UpdateGreat();
				
				evaluation->ui = UI::Great;
			}

			//隕石と一番離れている
			else if (direction < RADIUS_GOOD + sphereMeteorite.radius)
			{
				
				earnscore->UpdateGood();
				
				evaluation->ui = UI::Good;
			}

			//隕石と接触もしくは避けたら
			if (hit)
			{
				//隕石を消す
				meteorite/*[i]*/ = nullptr;
				delete meteorite/*[i]*/;
			}
		}
	}
}