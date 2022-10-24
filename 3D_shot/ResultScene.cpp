#include "ResultScene.h"
#include "DxLib.h"
#include "Common.h"
#include "HitChecker.h"
#include "SceneManager.h"


ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, hitchecker(nullptr)
	, resultImage(0)
	, resultBackgroundX(0)
	, resultBackgroundY(0)
	, score(0)
	, targetScore(0)
{
	//�����Ȃ�
}

ResultScene::~ResultScene()
{
	//�����Ȃ�
}

void ResultScene::Initialize()
{
	hitchecker = new HitChecker();
}

void ResultScene::Finalize()
{
}

void ResultScene::Activate()
{
}

void ResultScene::Update(float deltaTime)
{
	//HitChecker�̃X�R�A���擾
	targetScore = hitchecker->GetScore();

	//�X�R�A��ڕW�X�R�A�ɑ����������鏈��
	if (targetScore != score)
	{
		if (targetScore > score)
		{
			score += 100;
		}
		else
		{
			score -= 100;
		}
	}

	//���̃V�[����
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		parent->SetNextScene(SceneManager::TITLE);
		return;
	}
	else if (CheckHitKey(KEY_INPUT_B))
	{
		parent->SetNextScene(SceneManager::PLAY);
		return;
	}
}

void ResultScene::Draw()
{
	//�l���X�R�A�\��
	DrawFormatString(750, 400, GetColor(255, 255, 0), "�l��SCORE : %d", score);

	DrawFormatString(250, 800, GetColor(255, 255, 255), "Back�L�[��Title�ɖ߂� or B�L�[�ł�����x�v���C����");
}
