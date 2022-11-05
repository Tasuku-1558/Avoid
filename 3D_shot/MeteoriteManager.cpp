//#include "MeteoriteManager.h"
//#include "Meteorite.h"
//#include "Player.h"
//#include "Explosion.h"
//#include "Evaluation.h"
//#include "EarnScore.h"
//
//
//const float MeteoriteManager::RADIUS_GOOD		 = 1000.0f;	//goodの範囲
//const float MeteoriteManager::RADIUS_GREAT		 = 250.0f;	//greatの範囲
//const float MeteoriteManager::RADIUS_EXCELLENT   = 40.0f;	//excellentの範囲
//const float MeteoriteManager::RADIUS_MISS		 = 4.0f;	//missの範囲
//
//
//MeteoriteManager::MeteoriteManager()
//	: objects()
//	, direction(0.0f)
//	, hit(false)
//{
//	//処理なし
//}
//
//MeteoriteManager::~MeteoriteManager()
//{
//	ReleaseAllObj();
//}
//
////void MeteoriteManager::Initialize()
////{
////	if (!instance)
////	{
////		instance = Initialize(MeteoriteManager meteoriteManager);
////	}
////}
//
//void MeteoriteManager::Finalize(MeteoriteManager* p)
//{
//	/*ReleaseAllObj();
//	int i=0;
//	for (auto itr : p->instance)
//	{
//		if (p->instance)
//		{
//			delete instance;
//			instance = nullptr;
//		}
//	}*/
//	
//}
//
//void MeteoriteManager::Entry(Meteorite* newMeteorite)
//{
//	instance->pendingObjects.emplace_back(newMeteorite);
//}
//
//void MeteoriteManager::Release(Meteorite* releaseMeteorite)
//{
//	//pendingObjects内から検索
//	auto iter = std::find(instance->pendingObjects.begin(), instance->pendingObjects.end(), releaseMeteorite);
//
//	if (iter != instance->pendingObjects.end())
//	{
//		//最後尾に移動してデータを消す
//		std::iter_swap(iter, instance->pendingObjects.end() - 1);
//		instance->pendingObjects.pop_back();
//
//		return;
//	}
//
//	//objects内から検索
//	iter = std::find(instance->objects.begin(), instance->objects.end(), releaseMeteorite);
//
//	if (iter != instance->objects.end())
//	{
//		//最後尾に移動してデータを消す
//		std::iter_swap(iter, instance->objects.end() - 1);
//		delete instance->objects.back();
//	}
//}
//
//void MeteoriteManager::ReleaseAllObj()
//{
//	//末尾からpendingObjectsをすべて削除
//	while (!instance->pendingObjects.empty())
//	{
//		delete instance->pendingObjects.back();
//	}
//
//	while (!instance->objects.empty())
//	{
//		delete instance->objects.back();
//		instance->objects.pop_back();
//	}
//}
//
//void MeteoriteManager::Update(float deltaTime, Player* player)
//{
//	for (int i = 0; i < instance->objects.size(); ++i)
//	{
//		instance->objects[i]->Update(deltaTime, player);
//	}
//
//	for (auto pending : instance->pendingObjects)
//	{
//		instance->objects.emplace_back(pending);
//	}
//
//	instance->pendingObjects.clear();
//
//	std::vector<Meteorite*> deadMeteorite;
//
//	/*for (int i = 0; i < instance->objects.size(); ++i)
//	{
//		if (!instance->objects[i]->GetHit())
//		{
//			deadMeteorite.emplace_back(instance->objects[i]);
//		}
//	}*/
//	
//	//死んだオブジェクトをdelete
//	/*for (auto deadObj : deadMeteorite)
//	{
//		delete deadObj;
//	}
//
//	deadMeteorite.clear();*/
//}
//
//void MeteoriteManager::PlayerAndMeteorite(Player* player, Meteorite* meteorite, Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore)
//{
//	//for (int i = 0; i < instance->objects.size(); ++i)
//	//{
//	//	if (meteorite/*[i] */ != nullptr && meteorite/*[i]*/->GetPosition().z <= 10)
//	//	{
//			//当たったかどうか
//			hit = true;
//
//			//隕石の当たり判定球を取得
//			Math3d::Sphere sphereMeteorite = meteorite->GetCollisionSphere();
//
//			double posX = player->GetPosition().x - meteorite->GetPosition().x;
//			double posY = player->GetPosition().y - meteorite->GetPosition().y;
//
//			//プレイヤーと隕石の２点間の距離を計算
//			direction = sqrt(pow(posX, 2) + pow(posY, 2));
//
//
//			//隕石と衝突したら
//			if (direction < RADIUS_MISS + sphereMeteorite.radius)
//			{
//
//				earnscore->UpdateMiss();
//
//				evaluation->ui = UI::Miss;
//			}
//
//			//隕石とギリギリの範囲
//			else if (direction < RADIUS_EXCELLENT + sphereMeteorite.radius)
//			{
//
//				earnscore->UpdateExcellent();
//
//				evaluation->ui = UI::Excellent;
//
//				explosion->Update(meteorite);
//			}
//
//			//隕石と中くらいの範囲
//			else if (direction < RADIUS_GREAT + sphereMeteorite.radius)
//			{
//
//				earnscore->UpdateGreat();
//
//				evaluation->ui = UI::Great;
//			}
//
//			//隕石と一番離れている
//			else if (direction < RADIUS_GOOD + sphereMeteorite.radius)
//			{
//
//				earnscore->UpdateGood();
//
//				evaluation->ui = UI::Good;
//			}
//
//			//隕石と接触もしくは避けたら
//			if (hit)
//			{
//				//隕石を消す
//				meteorite = nullptr;
//				delete meteorite;
//			}
//	/*	}
//	}*/
//}
//
//void MeteoriteManager::Draw()
//{
//	for (auto i : instance->pendingObjects)
//	{
//		i->Draw();
//	}
//}