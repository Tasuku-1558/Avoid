#include "ResultScene.h"
#include "DxLib.h"

#include "PreCompiledHeader.h"
#include "BackGround.h"
#include "Score.h"


const string ResultScene::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string ResultScene::RESULT_UI_PATH	= "ResultUi.png";		//リプレイ、タイトルへのUI画像のパス
const string ResultScene::SCORE_GAUGE_PATH  = "ScoreGauge.png";		//スコアゲージ枠画像のパス
const string ResultScene::SCORE_B_PATH		= "ScoreB.png";			//B評価画像のパス
const string ResultScene::SCORE_A_PATH		= "ScoreA.png";			//A評価画像のパス
const string ResultScene::SCORE_S_PATH		= "ScoreS.png";			//S評価画像のパス


ResultScene::ResultScene()
	: SceneBase(SceneType::RESULT)
	, state()
	, frame(0.0f)
	, pUpdate(nullptr)
	, totalScore(0)
	, excellentCount(0)
	, greatCount(0)
	, goodCount(0)
	, missCount(0)
	, displayCount(0.0f)
	, resultUi(0)
	, scoreFont(0)
	, evaluationFont(0)
	, scoreGauge(0.0f)
	, scoreMaxGauge(0.0f)
	, scoreGaugeFrame(0)
	, scoreB(0)
	, scoreA(0)
	, scoreS(0)
	, alpha(0)
	, inc(0)
{
	Initialize();
	Activate();
}

ResultScene::~ResultScene()
{
	Finalize();
}

void ResultScene::Initialize()
{
	background = new BackGround();

	string failePath = IMAGE_FOLDER_PATH + RESULT_UI_PATH;
	resultUi = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + SCORE_GAUGE_PATH;
	scoreGaugeFrame = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + SCORE_B_PATH;
	scoreB = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + SCORE_A_PATH;
	scoreA = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + SCORE_S_PATH;
	scoreS = LoadGraph(failePath.c_str());
}

void ResultScene::Finalize()
{
	delete background;

	DeleteFontToHandle(scoreFont);
	DeleteFontToHandle(evaluationFont);

	DeleteGraph(resultUi);
	DeleteGraph(scoreGaugeFrame);
	DeleteGraph(scoreB);
	DeleteGraph(scoreA);
	DeleteGraph(scoreS);
}

void ResultScene::Activate()
{
	state = State::START;
	pUpdate = &ResultScene::UpdateStart;

	alpha = 255;
	inc = -1;
	
	scoreFont	   = CreateFontToHandle("Oranienbaum", 130, 1);
	evaluationFont = CreateFontToHandle("Oranienbaum", 80, 1);
}

/// <summary>
/// スコアを取得
/// </summary>
void ResultScene::AcquisitionScore()
{
	totalScore	   = Score::GetInstance().GetScore();
	excellentCount = Score::GetInstance().GetExcellentCount();
	greatCount	   = Score::GetInstance().GetGreatCount();
	goodCount	   = Score::GetInstance().GetGoodCount();
	missCount	   = Score::GetInstance().GetMissCount();
}

SceneType ResultScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		//状態ごとに更新

		return nowSceneType;
	}
}

void ResultScene::UpdateStart()
{
	state = State::GAME;
	pUpdate = &ResultScene::UpdateGame;
}

void ResultScene::UpdateGame()
{
	state = State::RESULT;
	pUpdate = &ResultScene::UpdateResult;

	AcquisitionScore();
}

void ResultScene::UpdateResult()
{
	Score::GetInstance().Activate();

	//タイトル画面へ
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		nowSceneType = SceneType::TITLE;
	}

	//もう一度プレイする
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		nowSceneType = SceneType::PLAY;
	}
}

/// <summary>
/// 獲得スコア表示
/// </summary>
void ResultScene::DisplayScore()
{
	displayCount += 1.0f;

	if (displayCount > 10.0f)
	{
		DrawFormatStringToHandle(650, 250, GetColor(255, 69, 0), scoreFont, "SCORE : %d",  totalScore);

		if (displayCount > 30.0f)
		{
			DrawFormatStringToHandle(650, 400, GetColor(255, 255, 0), evaluationFont, "Excellent   ×  %d", excellentCount);
			if (displayCount > 50.0f)
			{
				DrawFormatStringToHandle(650, 500, GetColor(255, 105, 180), evaluationFont, "Great         ×  %d", greatCount);
				if (displayCount > 70.0f)
				{
					DrawFormatStringToHandle(650, 600, GetColor(175, 238, 238), evaluationFont, "Good          ×  %d", goodCount);
					if (displayCount > 90.0f)
					{
						DrawFormatStringToHandle(650, 700, GetColor(169, 169, 169), evaluationFont, "Miss          ×  %d", missCount);
						displayCount = 90.0f;
					}
				}
			}
		}
	}
}

/// <summary>
/// 文字の点滅
/// </summary>
void ResultScene::Blink()
{
	if (alpha > 255 && inc > 0)
		inc *= -1;

	if (alpha < 0 && inc < 0)
		inc *= -1;

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawGraph(1150, 850, resultUi, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// スコアゲージ表示
/// </summary>
void ResultScene::ScoreGauge()
{
	scoreMaxGauge = 100.0f;
	
	
	DrawBox(500, 200, 500 + 200 * (scoreGauge / scoreMaxGauge), 117, GetColor(186, 85, 211), TRUE);	//スコアゲージを描画
	DrawGraph(218, -270, scoreGaugeFrame, TRUE);		//スコアゲージ枠を描画

	scoreGauge += 1.0f;

	if (scoreGauge >= scoreMaxGauge)
	{
		//B判定
		if (totalScore >= 0 || totalScore >= 10000)
		{
			scoreGauge = 180.0f;
			//scoreGauge = scoreMaxGauge;
		
			
			DrawRotaGraph(1450, 150, 1.0f, 0.5, scoreB, TRUE);
		}

		//A判定
		if (totalScore >= 18000)
		{
			scoreGauge = 265.0f;
			//scoreGauge = scoreMaxGauge;
		

			DrawRotaGraph(1450, 150, 1.0f, 0.5, scoreA, TRUE);
		}

		//S判定
		if (totalScore >= 21000)
		{
			scoreGauge = 350.0f;
			//scoreGauge = scoreMaxGauge;
		

			DrawRotaGraph(1450, 150, 1.0f, 0.5, scoreS, TRUE);
		}
	}
}

void ResultScene::Draw()
{
	background->Draw();

	//獲得スコア表示
	DisplayScore();

	Blink();

	//スコアゲージ表示
	ScoreGauge();
}