#include "MeteoriteManager.h"
#include "Meteorite.h"
#include "Player.h"
#include "HitChecker.h"

//MeteoriteManager���̂ւ̃|�C���^��`
MeteoriteManager* MeteoriteManager::instance = nullptr;

MeteoriteManager::MeteoriteManager()
	: objects()
{
	instance = nullptr;
}

MeteoriteManager::~MeteoriteManager()
{
	ReleaseAllObj();
}

void MeteoriteManager::Initialize()
{
	if (!instance)
	{
		instance = new MeteoriteManager;
	}
}

void MeteoriteManager::Finalize()
{
	ReleaseAllObj();
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void MeteoriteManager::Entry(Meteorite* newObj)
{
	instance->pendingObjects.emplace_back(newObj);
}

void MeteoriteManager::Release(Meteorite* releaseObj)
{
	//pendingObjects�����猟��
	auto iter = std::find(instance->pendingObjects.begin(), instance->pendingObjects.end(), releaseObj);

	if (iter != instance->pendingObjects.end())
	{
		//�Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, instance->pendingObjects.end() - 1);
		instance->pendingObjects.pop_back();

		return;
	}

	//objects�����猟��
	iter = std::find(instance->objects.begin(), instance->objects.end(), releaseObj);

	if (iter != instance->objects.end())
	{
		//�Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, instance->objects.end() - 1);
		delete instance->objects.back();
	}
}

void MeteoriteManager::ReleaseAllObj()
{
	//��������pendingObjects�����ׂč폜
	while (!instance->pendingObjects.empty())
	{
		delete instance->pendingObjects.back();
	}

	while (!instance->objects.empty())
	{
		delete instance->objects.back();
		instance->objects.pop_back();
	}
}

void MeteoriteManager::Update(float deltaTime, Player* player)
{
	for (int i = 0; i < instance->objects.size(); ++i)
	{
		instance->objects[i]->Update(deltaTime, player);
	}

	for (auto pending : instance->pendingObjects)
	{
		instance->objects.emplace_back(pending);
	}

	instance->pendingObjects.clear();

	std::vector<Meteorite*> deadMeteorite;

	/*for (int i = 0; i < instance->objects.size(); ++i)
	{
		if (!instance->objects[i]->GetHit())
		{
			deadMeteorite.emplace_back(instance->objects[i]);
		}
	}*/
	
	//���񂾃I�u�W�F�N�g��delete
	/*for (auto deadObj : deadMeteorite)
	{
		delete deadObj;
	}

	deadMeteorite.clear();*/
}

void MeteoriteManager::Draw()
{
	for (int i = 0; i < instance->objects.size(); ++i)
	{
		instance->objects[i]->Draw();
	}
}