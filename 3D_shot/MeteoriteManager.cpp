//#include "MeteoriteManager.h"
//#include "Meteorite.h"
//#include "Player.h"
////#include "HitChecker.h"
//#include "Explosion.h"
//#include "Evaluation.h"
//#include "EarnScore.h"
//
//
//const float MeteoriteManager::RADIUS_GOOD		 = 1000.0f;	//good�͈̔�
//const float MeteoriteManager::RADIUS_GREAT		 = 250.0f;	//great�͈̔�
//const float MeteoriteManager::RADIUS_EXCELLENT   = 40.0f;	//excellent�͈̔�
//const float MeteoriteManager::RADIUS_MISS		 = 4.0f;	//miss�͈̔�
//
//
//MeteoriteManager::MeteoriteManager()
//	: objects()
//	, direction(0.0f)
//	, hit(false)
//{
//	//�����Ȃ�
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
//void MeteoriteManager::Finalize()
//{
//	ReleaseAllObj();
//	if (instance)
//	{
//		delete instance;
//		instance = nullptr;
//	}
//}
//
//void MeteoriteManager::Entry(Meteorite* newObj)
//{
//	instance->pendingObjects.emplace_back(newObj);
//}
//
//void MeteoriteManager::Release(Meteorite* releaseObj)
//{
//	//pendingObjects�����猟��
//	auto iter = std::find(instance->pendingObjects.begin(), instance->pendingObjects.end(), releaseObj);
//
//	if (iter != instance->pendingObjects.end())
//	{
//		//�Ō���Ɉړ����ăf�[�^������
//		std::iter_swap(iter, instance->pendingObjects.end() - 1);
//		instance->pendingObjects.pop_back();
//
//		return;
//	}
//
//	//objects�����猟��
//	iter = std::find(instance->objects.begin(), instance->objects.end(), releaseObj);
//
//	if (iter != instance->objects.end())
//	{
//		//�Ō���Ɉړ����ăf�[�^������
//		std::iter_swap(iter, instance->objects.end() - 1);
//		delete instance->objects.back();
//	}
//}
//
//void MeteoriteManager::ReleaseAllObj()
//{
//	//��������pendingObjects�����ׂč폜
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
//	//���񂾃I�u�W�F�N�g��delete
//	/*for (auto deadObj : deadMeteorite)
//	{
//		delete deadObj;
//	}
//
//	deadMeteorite.clear();*/
//}
//
//void MeteoriteManager::PlayerAndMeteorite(Player* player, /*Meteorite* meteorite[]*/Meteorite* meteorite, Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore)
//{
//	for (int i = 0; i < /*Meteorite::METEORITE_ARRAY_NUMBER;*/instance->objects.size(); ++i)
//	{
//		if (meteorite/*[i] */ != nullptr && meteorite/*[i]*/->GetPosition().z <= 10)
//		{
//			//�����������ǂ���
//			hit = true;
//
//			//覐΂̓����蔻�苅���擾
//			Math3d::Sphere sphereMeteorite = meteorite/*[i]*/->GetCollisionSphere();
//
//			double posX = player->GetPosition().x - meteorite/*[i]*/->GetPosition().x;
//			double posY = player->GetPosition().y - meteorite/*[i]*/->GetPosition().y;
//
//			//�v���C���[��覐΂̂Q�_�Ԃ̋������v�Z
//			direction = sqrt(pow(posX, 2) + pow(posY, 2));
//
//
//			//覐΂ƏՓ˂�����
//			if (direction < RADIUS_MISS + sphereMeteorite.radius)
//			{
//
//				earnscore->UpdateMiss();
//
//				evaluation->ui = UI::Miss;
//			}
//
//			//覐΂ƃM���M���͈̔�
//			else if (direction < RADIUS_EXCELLENT + sphereMeteorite.radius)
//			{
//
//				earnscore->UpdateExcellent();
//
//				evaluation->ui = UI::Excellent;
//
//				explosion->Update(meteorite/*[i]*/);
//			}
//
//			//覐΂ƒ����炢�͈̔�
//			else if (direction < RADIUS_GREAT + sphereMeteorite.radius)
//			{
//
//				earnscore->UpdateGreat();
//
//				evaluation->ui = UI::Great;
//			}
//
//			//覐΂ƈ�ԗ���Ă���
//			else if (direction < RADIUS_GOOD + sphereMeteorite.radius)
//			{
//
//				earnscore->UpdateGood();
//
//				evaluation->ui = UI::Good;
//			}
//
//			//覐΂ƐڐG�������͔�������
//			if (hit)
//			{
//				//覐΂�����
//				meteorite/*[i]*/ = nullptr;
//				delete meteorite/*[i]*/;
//			}
//		}
//	}
//}
//
//void MeteoriteManager::Draw()
//{
//	for (auto i : instance->pendingObjects)
//	{
//		i->Draw();
//	}
//}