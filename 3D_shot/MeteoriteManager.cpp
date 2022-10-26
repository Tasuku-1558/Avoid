#include "MeteoriteManager.h"
#include "Player.h"
#include "Meteorite.h"


//MeteoriteManager実体へのポインタ定義
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
	//pendingObjects内から検索
	auto iter = std::find(instance->pendingObjects.begin(), instance->pendingObjects.end(), releaseObj);

	if (iter != instance->pendingObjects.end())
	{
		//最後尾に移動してデータを消す
		std::iter_swap(iter, instance->pendingObjects.end() - 1);
		instance->pendingObjects.pop_back();

		return;
	}

	//objects内から検索
	iter = std::find(instance->objects.begin(), instance->objects.end(), releaseObj);

	if (iter != instance->objects.end())
	{
		//最後尾に移動してデータを消す
		std::iter_swap(iter, instance->objects.end() - 1);
		delete instance->objects.back();
	}
}

void MeteoriteManager::ReleaseAllObj()
{
	//末尾からpendingObjectsをすべて削除
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

	std::vector<Meteorite*> deadObjects;

	for (int i = 0; i < instance->objects.size(); ++i)
	{
		/*if (!instance->objects[i])
		{
			deadObjects.emplace_back(instance->objects[i]);
		}*/
	}
	
	for (auto deadObj : deadObjects)
	{
		delete deadObj;
	}

	deadObjects.clear();
}

void MeteoriteManager::Draw()
{
	for (int i = 0; i < instance->objects.size(); ++i)
	{
		instance->objects[i]->Draw();
	}
}

int MeteoriteManager::GetSize()
{
	return instance->pendingObjects.size();
}