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
	, feverGauge(0.0f)
	, count(0)
{
	//処理なし
}

ResultScene::~ResultScene()
{
	//処理なし
}

void ResultScene::Initialize()
{
	//背景クラス
	background = new BackGround();
	background->Initialize();

	resultUi = LoadGraph("data/image/ResultUi.png");
}

void ResultScene::Finalize()
{
	//背景クラス
	SafeDelete(background);
	background->Finalize();

	DeleteFontToHandle(scoreFont);
	DeleteFontToHandle(font);
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

//スコアを取得
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
		(this->*pUpdate)();		//状態ごとに更新
	}

	++frame;
}

void ResultScene::UpdateStart()
{
	frame = 0;
	displayCount = 0.0f;
	feverGauge = 0.0f;
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

	//次のシーンへ
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

//獲得スコア表示
void ResultScene::DisplayScore()
{
	displayCount += 1.0f;

	if (displayCount > 10.0f)
	{
		DrawFormatStringToHandle(650, 250, GetColor(255, 69, 0), scoreFont, "SCORE : %d",  totalScore);

		if (displayCount > 30.0f)
		{
			DrawFormatStringToHandle(650, 400, GetColor(255, 255, 0), font, "Excellent   ×  %d", excellentCount);
			if (displayCount > 50.0f)
			{
				DrawFormatStringToHandle(650, 500, GetColor(255, 105, 180), font, "Great         ×  %d", greatCount);
				if (displayCount > 70.0f)
				{
					DrawFormatStringToHandle(650, 600, GetColor(175, 238, 238), font, "Good          ×  %d", goodCount);
					if (displayCount > 90.0f)
					{
						DrawFormatStringToHandle(650, 700, GetColor(169, 169, 169), font, "Miss          ×  %d", missCount);
						displayCount = 90.0f;
					}
				}
			}
		}
	}
}

void ResultScene::Blink()
{
	// 明滅ルーチン
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

void ResultScene::ScoreGauge()
{
	float feverMaxGauge = 100.0f;
	count += 1;
	if (count > 20)
	{
		feverGauge = totalScore / static_cast<float>(50);
		count = 0;
	}
	
	DrawBox(200, 20, 310 + 850 * (feverGauge / feverMaxGauge), 110, GetColor(186, 85, 211), FALSE);
}

void ResultScene::Draw()
{
	//背景描画
	background->Draw();

	//獲得スコア表示
	DisplayScore();

	Blink();

	ScoreGauge();
}