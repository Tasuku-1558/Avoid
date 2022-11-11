#include "HitChecker.h"
#include "TimeSlow.h"
#include "Player.h"
#include "Meteorite.h"
#include "Explosion.h"
#include "Evaluation.h"
#include "EarnScore.h"
#include <math.h>


using namespace std;

const float HitChecker::RADIUS_GOOD		 = 1000.0f;	//good‚Ì”ÍˆÍ
const float HitChecker::RADIUS_GREAT	 = 250.0f;	//great‚Ì”ÍˆÍ
const float HitChecker::RADIUS_EXCELLENT = 40.0f;	//excellent‚Ì”ÍˆÍ
const float HitChecker::RADIUS_MISS		 = 4.0f;	//miss‚Ì”ÍˆÍ


HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, count(0.0f)
	, slow(false)
{
	//ˆ—‚È‚µ
}

HitChecker::~HitChecker()
{
	//ˆ—‚È‚µ
}

void HitChecker::PlayerAndMeteorite(Player* player, Meteorite* meteorite[], Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore)
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; ++i)
	{
		if (meteorite[i] != nullptr && meteorite[i]->GetPosition().z <= 10)
		{
			//“–‚½‚Á‚½‚©‚Ç‚¤‚©
			hit = true;

			//è¦Î‚Ì“–‚½‚è”»’è‹…‚ğæ“¾
			Math3d::Sphere sphereMeteorite = meteorite[i]->GetCollisionSphere();

			double posX = player->GetPosition().x - meteorite[i]->GetPosition().x;
			double posY = player->GetPosition().y - meteorite[i]->GetPosition().y;

			//ƒvƒŒƒCƒ„[‚Æè¦Î‚Ì‚Q“_ŠÔ‚Ì‹——£‚ğŒvZ
			direction = sqrt(pow(posX, 2) + pow(posY, 2));

			//è¦Î‚ÆÕ“Ë‚µ‚½‚ç
			if (direction < RADIUS_MISS + sphereMeteorite.radius)
			{
				earnscore->UpdateMiss();

				evaluation->ui = UI::Miss;

				player->state = State::Damage;
			}

			//è¦Î‚ÆƒMƒŠƒMƒŠ‚Ì”ÍˆÍ
			else if (direction < RADIUS_EXCELLENT + sphereMeteorite.radius)
			{

				earnscore->UpdateExcellent();

				evaluation->ui = UI::Excellent;

				explosion->Update(meteorite[i]);

				slow = true;
				TimeSlow::GetInstance().SetTimeSlow(slow);

			}

			//è¦Î‚Æ’†‚­‚ç‚¢‚Ì”ÍˆÍ
			else if (direction < RADIUS_GREAT + sphereMeteorite.radius)
			{

				earnscore->UpdateGreat();

				evaluation->ui = UI::Great;
			}

			//è¦Î‚Æˆê”Ô—£‚ê‚Ä‚¢‚é
			else if (direction < RADIUS_GOOD + sphereMeteorite.radius)
			{

				earnscore->UpdateGood();

				evaluation->ui = UI::Good;
			}

			//è¦Î‚ÆÚG‚à‚µ‚­‚Í”ğ‚¯‚½‚ç
			if (hit)
			{
				//è¦Î‚ğÁ‚·
				meteorite[i] = nullptr;
				delete meteorite[i];
			}
		}
	}
}