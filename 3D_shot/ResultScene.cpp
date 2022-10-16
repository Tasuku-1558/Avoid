#include "ResultScene.h"
#include "DxLib.h"
#include "HitChecker.h"


ResultScene::ResultScene():SceneBase(SceneType::RESULT)
	, hitchecker(new HitChecker())
	, ResultImage(0)
	, ResultBackgroundX(0)
	, ResultBackgroundY(0)
	, Score(0)
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
	//HitChecker�̃X�R�A���擾
	Score = hitchecker->GetScore();

	////�X�R�A��ڕW�X�R�A�ɑ����������鏈��
	//if (TargetScore != Score)
	//{
	//	if (TargetScore > Score)
	//	{
	//		Score += 100;
	//	}
	//	else
	//	{
	//		Score -= 100;
	//	}
	//}

	//���̃V�[����
	if (CheckHitKey(KEY_INPUT_BACK))
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
	//�l���X�R�A�\��
	DrawFormatString(750, 400, GetColor(255, 255, 0), "�l��SCORE : %d", Score);

	DrawFormatString(250, 800, GetColor(255, 255, 255), "Back�L�[��Title�ɖ߂� or B�L�[�ł�����x�v���C����");
}
