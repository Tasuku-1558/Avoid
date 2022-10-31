#include "HitChecker.h"
#include "Player.h"
#include "MeteoriteManager.h"
#include "Meteorite.h"
#include "Explosion.h"
#include "Evaluation.h"
#include "Score.h"

using namespace std;

const float HitChecker::RADIUS_GOOD		 = 1000.0f;	//goodの範囲
const float HitChecker::RADIUS_GREAT	 = 250.0f;	//greatの範囲
const float HitChecker::RADIUS_EXCELLENT = 40.0f;	//excellentの範囲
const float HitChecker::RADIUS_MISS		 = 4.0f;	//missの範囲

const int	HitChecker::SCORE_GOOD		 = 100;		//goodのスコア
const int	HitChecker::SCORE_GREAT		 = 200;		//greatのスコア
const int	HitChecker::SCORE_EXCELLENT  = 600;		//excellentのスコア
const int	HitChecker::SCORE_MISS		 = 300;		//missのスコア

const int	HitChecker::FIRST_SCORE		 = 0;		//スコアの初期値


HitChecker::HitChecker()
	: score(0)
	, direction(0.0f)
	, hit(false)
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
}

void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite[]/*vector<Meteorite*> meteorite*/, MeteoriteManager* meteoriteManager, Explosion* explosion,Evaluation* evaluation)
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER;/*meteoriteManager->GetSize();*/ ++i)
	{
		if (meteorite[i] != nullptr && meteorite[i]->GetPosition().z <= 10)
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
				score -= SCORE_MISS;
				Score::GetInstance().SetScore(score);
				evaluation->ui = UI::Miss;
				
			}

			//隕石とギリギリの範囲
			else if (direction < RADIUS_EXCELLENT + sphereMeteorite.radius)
			{
				score += SCORE_EXCELLENT;
				Score::GetInstance().SetScore(score);
				evaluation->ui = UI::Excellent;

				explosion->Update(meteorite[i]);
			}
			
			//隕石と中くらいの範囲
			else if (direction < RADIUS_GREAT + sphereMeteorite.radius)
			{
				score += SCORE_GREAT;
				Score::GetInstance().SetScore(score);
				evaluation->ui = UI::Great;
			}

			//隕石と一番離れている
			else if (direction < RADIUS_GOOD + sphereMeteorite.radius)
			{
				score += SCORE_GOOD;
				Score::GetInstance().SetScore(score);
				evaluation->ui = UI::Good;
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