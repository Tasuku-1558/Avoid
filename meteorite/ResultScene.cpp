#include "ResultScene.h"
#include "DxLib.h"


ResultScene::ResultScene():SceneBase(SceneType::RESULT)
{
	//ˆ—‚È‚µ
}

ResultScene::~ResultScene()
{
	//ˆ—‚È‚µ
}

void ResultScene::Initialize()
{
}

SceneType ResultScene::Update(float deltaTime)
{
	//Ÿ‚ÌƒV[ƒ“‚Ö
	if (CheckHitKey(KEY_INPUT_B))
	{
		NowSceneType = SceneType::TITLE;
	}

	return NowSceneType;
}

void ResultScene::Draw()
{
}
