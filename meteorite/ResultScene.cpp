#include "ResultScene.h"
#include "DxLib.h"


ResultScene::ResultScene():SceneBase(SceneType::RESULT)
{
	//処理なし
}

ResultScene::~ResultScene()
{
	//処理なし
}

void ResultScene::Initialize()
{
}

SceneType ResultScene::Update(float deltaTime)
{
	//次のシーンへ
	if (CheckHitKey(KEY_INPUT_B))
	{
		NowSceneType = SceneType::TITLE;
	}

	return NowSceneType;
}

void ResultScene::Draw()
{
}
