#include "ResultScene.h"
#include "DxLib.h"


ResultScene::ResultScene():SceneBase(SceneType::RESULT)
	, ResultImage(0)
	, ResultBackgroundX(0)
	, ResultBackgroundY(0)
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
	if (CheckHitKey(KEY_INPUT_A))
	{
		NowSceneType = SceneType::TITLE;
	}
	else if (CheckHitKey(KEY_INPUT_B))
	{
		NowSceneType = SceneType::PLAY;
	}

	return NowSceneType;
}

void ResultScene::Draw()
{
}
