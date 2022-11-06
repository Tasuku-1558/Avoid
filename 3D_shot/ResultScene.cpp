#include "ResultScene.h"
#include "DxLib.h"
#include "Common.h"
#include "BackGround.h"
#include "Score.h"
#include "SceneManager.h"


ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, frame(0)
	, background(nullptr)
	, pUpdate(nullptr)
	, totalScore(0)
	, excellentCount(0)
	, greatCount(0)
	, goodCount(0)
	, missCount(0)
	, count(0.0f)
{
	//�����Ȃ�
}

ResultScene::~ResultScene()
{
	//�����Ȃ�
}

void ResultScene::Initialize()
{
	//�w�i�N���X
	background = new BackGround();
	background->Initialize();
}

void ResultScene::Finalize()
{
	//�w�i�N���X
	SafeDelete(background);
	background->Finalize();
}

void ResultScene::Activate()
{
	state = START;
	frame = 0;

	pUpdate = &ResultScene::UpdateStart;

	background->Activate();
}

//�X�R�A���擾
void ResultScene::AcquisitionScore()
{
	totalScore	   = Score::GetInstance().GetScore();
	excellentCount = Score::GetInstance().GetExcellentCount();
	greatCount	   = Score::GetInstance().GetGreatCount();
	goodCount	   = Score::GetInstance().GetGoodCount();
	missCount	   = Score::GetInstance().GetMissCount();
}

void ResultScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		//��Ԃ��ƂɍX�V
	}

	++frame;
}

void ResultScene::UpdateStart()
{
	frame = 0;
	count = 0.0f;
	state = GAME;

	pUpdate = &ResultScene::UpdateGame;
}

void ResultScene::UpdateGame()
{
	state = RESULT;
	pUpdate = &ResultScene::UpdateResult;

	AcquisitionScore();
}

void ResultScene::UpdateResult()
{
	Score::GetInstance().Activate();

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

//�l���X�R�A�\��
void ResultScene::DisplayScore()
{
	count += 1.0f;
	if (count > 10.0f)
	{
		DrawFormatString(650, 300, GetColor(255, 69, 0), "TOTAL_SCORE :  %d", totalScore);
		if (count > 30.0f)
		{
			DrawFormatString(650, 400, GetColor(255, 255, 0), "Excellent        �~ %d", excellentCount);
			if (count > 50.0f)
			{
				DrawFormatString(650, 500, GetColor(255, 105, 180), "Great              �~ %d", greatCount);
				if (count > 70.0f)
				{
					DrawFormatString(650, 600, GetColor(175, 238, 238), "Good               �~ %d", goodCount);
					if (count > 90.0f)
					{
						DrawFormatString(650, 700, GetColor(169, 169, 169), "MISS               �~ %d", missCount);
						count = 90.0f;
					}
				}
			}
		}
	}
}

void ResultScene::Blink()
{
	// ���Ń��[�`��
	static int Alpha = 0;
	static int Inc = 3;

	if (Alpha > 255 && Inc > 0)
		Inc *= -1;

	if (Alpha < 0 && Inc < 0)
		Inc *= -1;

	Alpha += Inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);

	DrawFormatString(400, 850, GetColor(255, 255, 255), "Back_Key : Title  or  Return_Key : Game");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);
}

void ResultScene::Draw()
{
	//�w�i�`��
	background->Draw();

	SetFontSize(70);			//�����̃t�H���g�T�C�Y�ύX

	//�l���X�R�A�\��
	DisplayScore();

	Blink();
}