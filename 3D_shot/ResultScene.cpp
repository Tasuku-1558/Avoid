#include "ResultScene.h"
#include "DxLib.h"
#include "Common.h"
#include "Score.h"
#include "SceneManager.h"


ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, resultBackGround(0)
	, totalScore(0)
	, score(0)
	, excellentCount(0)
	, scoreE(0)
	, greatCount(0)
	, scoreG(0)
	, goodCount(0)
	, scoreD(0)
	, missCount(0)
	, scoreM(0)
{
	//処理なし
}

ResultScene::~ResultScene()
{
	//処理なし
}

void ResultScene::Initialize()
{
	//リザルト背景
	resultBackGround = LoadGraph("data/image/GameBackground.png");
}

void ResultScene::Finalize()
{
	//リザルト背景を解放
	DeleteGraph(resultBackGround);
}

void ResultScene::Activate()
{
	totalScore = 0;
	excellentCount = 0;
	greatCount = 0;
	goodCount = 0;
	missCount = 0;

	score = 0;
	scoreE = 0;
	scoreG = 0;
	scoreD = 0;
	scoreM = 0;
}

//スコアを取得
void ResultScene::AcquisitionScore()
{
	totalScore = Score::GetInstance().GetScore();
	excellentCount = Score::GetInstance().GetExcellentCount();
	greatCount = Score::GetInstance().GetGreatCount();
	goodCount = Score::GetInstance().GetGoodCount();
	missCount = Score::GetInstance().GetMissCount();
}

//スコア計算
void ResultScene::ScoreCalculation()
{
	//スコアを目標スコアに足し引きする処理
	if (totalScore != score)
	{
		if (totalScore > score)
		{
			score += 100;
		}
	}
	if (excellentCount != scoreE)
	{
		if (excellentCount > scoreE)
		{
			scoreE += 1;
		}
	}
	if (greatCount != scoreG)
	{
		if (greatCount > scoreG)
		{
			scoreG += 1;
		}
	}
	if (goodCount != scoreD)
	{
		if (goodCount > scoreD)
		{
			scoreD += 1;
		}
	}
	if (missCount != scoreM)
	{
		if (missCount > scoreM)
		{
			scoreM += 1;
		}
	}
}

void ResultScene::Update(float deltaTime)
{
	AcquisitionScore();
	
	ScoreCalculation();

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

void ResultScene::Draw()
{
	//リザルト背景描画
	DrawBillboard3D(VGet(0.0f, 300.0f, 1200.0f), 0.5f, 0.5f, 4000.0f, 0.0f, resultBackGround, TRUE);

	SetFontSize(60);			//文字のフォントサイズ変更

	//獲得スコア表示
	DrawFormatString(750, 300, GetColor(255,   0,	0),	"TOTAL_SCORE : %d", score);
	DrawFormatString(750, 400, GetColor(255, 255,	0),	"Excellent  × %d", scoreE);
	DrawFormatString(750, 500, GetColor(255, 105, 180), "Great      × %d", scoreG);
	DrawFormatString(750, 600, GetColor(175, 238, 238), "Good       × %d", scoreD);
	DrawFormatString(750, 700, GetColor(169, 169, 169),	"MISS       × %d", scoreM);
	DrawFormatString(150, 800, GetColor(255, 255, 255), "BackキーでTitleに戻る or Returnキーでもう一度プレイする");
}