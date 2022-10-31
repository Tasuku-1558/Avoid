#include "ResultScene.h"
#include "DxLib.h"
#include "Common.h"
#include "Score.h"
#include "SceneManager.h"


ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, resultBackGround(0)
	, scoreR(0)
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
	scoreR = 0;
}

void ResultScene::SetScore()
{
	//�X�R�A���擾
	targetScore = Score::GetInstance().GetScore();
}

void ResultScene::Update(float deltaTime)
{
	SetScore();

	//�X�R�A��ڕW�X�R�A�ɑ����������鏈��
	if (targetScore != scoreR)
	{
		if (targetScore > scoreR)
		{
			scoreR += 100;
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

	//�l���X�R�A�\��
	DrawFormatString(750, 400, GetColor(255, 255, 0), "�l��SCORE : %d", scoreR);

	DrawFormatString(150, 800, GetColor(255, 255, 255), "Back�L�[��Title�ɖ߂� or Return�L�[�ł�����x�v���C����");
}
