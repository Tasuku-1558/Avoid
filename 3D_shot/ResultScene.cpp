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
	//処理なし
}

ResultScene::~ResultScene()
{
	//処理なし
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
	//HitCheckerのスコアを取得
	targetScore = hitchecker->GetScore();

	//スコアを目標スコアに足し引きする処理
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

	//次のシーンへ
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
	//獲得スコア表示
	DrawFormatString(750, 400, GetColor(255, 255, 0), "獲得SCORE : %d", score);

	DrawFormatString(250, 800, GetColor(255, 255, 255), "BackキーでTitleに戻る or Bキーでもう一度プレイする");
}
