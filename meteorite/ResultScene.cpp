#include "ResultScene.h"
#include "DxLib.h"


ResultScene::ResultScene():SceneBase(SceneType::RESULT)
{
	//�����Ȃ�
}

ResultScene::~ResultScene()
{
	//�����Ȃ�
}

void ResultScene::Initialize()
{
}

SceneType ResultScene::Update(float deltaTime)
{
	//���̃V�[����
	if (CheckHitKey(KEY_INPUT_B))
	{
		NowSceneType = SceneType::TITLE;
	}

	return NowSceneType;
}

void ResultScene::Draw()
{
}
