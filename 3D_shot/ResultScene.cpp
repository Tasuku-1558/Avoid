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
	, displayCount(0.0f)
	, resultUi(0)
	, scoreFont(0)
	, font(0)
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

	resultUi = LoadGraph("data/image/ResultUi.png");
}

void ResultScene::Finalize()
{
	//�w�i�N���X
	SafeDelete(background);
	background->Finalize();

	DeleteFontToHandle(scoreFont);
}

void ResultScene::Activate()
{
	state = START;
	frame = 0;
	
	scoreFont = CreateFontToHandle("Oranienbaum", 130, 1);
	font = CreateFontToHandle("Oranienbaum", 80, 1);
	
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
	displayCount = 0.0f;
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
	displayCount += 1.0f;

	if (displayCount > 10.0f)
	{
		DrawFormatStringToHandle(650, 250, GetColor(255, 69, 0), scoreFont, "SCORE : %d",  totalScore);

		if (displayCount > 30.0f)
		{
			DrawFormatStringToHandle(650, 400, GetColor(255, 255, 0), font, "Excellent   �~  %d", excellentCount);
			if (displayCount > 50.0f)
			{
				DrawFormatStringToHandle(650, 500, GetColor(255, 105, 180), font, "Great         �~  %d", greatCount);
				if (displayCount > 70.0f)
				{
					DrawFormatStringToHandle(650, 600, GetColor(175, 238, 238), font, "Good          �~  %d", goodCount);
					if (displayCount > 90.0f)
					{
						DrawFormatStringToHandle(650, 700, GetColor(169, 169, 169), font, "Miss          �~  %d", missCount);
						displayCount = 90.0f;
					}
				}
			}
		}
	}
}

void ResultScene::Blink()
{
	// ���Ń��[�`��
	static int alpha = 0;
	static int inc = 3;

	if (alpha > 255 && inc > 0)
		inc *= -1;

	if (alpha < 0 && inc < 0)
		inc *= -1;

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawGraph(1150, 850, resultUi, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

void ResultScene::Draw()
{
	//�w�i�`��
	background->Draw();

	//�l���X�R�A�\��
	DisplayScore();

	Blink();
}