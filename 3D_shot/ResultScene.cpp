#include "ResultScene.h"
#include "DxLib.h"
#include "Common.h"
#include "Score.h"
#include "SceneManager.h"


ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, resultBackGround(0)
	, totalScore(0)
	, tScore(0)
	, missScore(0)
	, mScore(0)
{
	//�����Ȃ�
}

ResultScene::~ResultScene()
{
	//�����Ȃ�
}

void ResultScene::Initialize()
{
	//���U���g�w�i
	resultBackGround = LoadGraph("data/image/GameBackground.png");
}

void ResultScene::Finalize()
{
	//���U���g�w�i�����
	DeleteGraph(resultBackGround);
}

void ResultScene::Activate()
{
	totalScore = 0;
}

void ResultScene::SetScore()
{
	//�X�R�A���擾
	totalScore = Score::GetInstance().GetScore();
	missScore = Score::GetInstance().GetMissScore();
}

void ResultScene::Update(float deltaTime)
{
	SetScore();

	//�X�R�A��ڕW�X�R�A�ɑ����������鏈��
	if (totalScore != tScore)
	{
		if (totalScore > tScore)
		{
			tScore += 100;
		}
	}
	
	else if (missScore != mScore)
	{
		if (missScore < mScore)
		{
			mScore -= 100;
		}
	}
	//���̃V�[����
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		parent->SetNextScene(SceneManager::TITLE);
		return;
	}
	else if (CheckHitKey(KEY_INPUT_RETURN))
	{
		parent->SetNextScene(SceneManager::PLAY);
		return;
	}
}

void ResultScene::Draw()
{
	//���U���g�w�i�`��
	DrawBillboard3D(VGet(0.0f, 300.0f, 1200.0f), 0.5f, 0.5f, 4000.0f, 0.0f, resultBackGround, TRUE);

	SetFontSize(60);			//�����̃t�H���g�T�C�Y�ύX

	//�l���X�R�A�\��
	DrawFormatString(750, 300, GetColor(255, 255, 0), "TOTAL_SCORE : %d", tScore);
	DrawFormatString(750, 400, GetColor(255, 255, 0), " MISS_SCORE : %d", mScore);


	DrawFormatString(150, 800, GetColor(255, 255, 255), "Back�L�[��Title�ɖ߂� or Return�L�[�ł�����x�v���C����");
}