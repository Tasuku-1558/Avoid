#include "ResultScene.h"
#include "DxLib.h"
#include "Common.h"
#include "HitChecker.h"
#include "SceneManager.h"


ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, hitchecker(nullptr)
	, resultBackGround(0)
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
	//リザルト背景
	resultBackGround = LoadGraph("data/image/GameBackground.png");

	hitchecker = new HitChecker();
}

void ResultScene::Finalize()
{
	//リザルト背景を解放
	DeleteGraph(resultBackGround);
}

void ResultScene::Activate()
{
	score = 0;
}

void ResultScene::Update(float deltaTime)
{
	//HitCheckerのスコアを取得
	targetScore = 10000;

	//スコアを目標スコアに足し引きする処理
	if (targetScore != score)
	{
		if (targetScore > score)
		{
			score += 100;
		}
	}

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

	//獲得スコア表示
	DrawFormatString(750, 400, GetColor(255, 255, 0), "獲得SCORE : %d", score);

	DrawFormatString(150, 800, GetColor(255, 255, 255), "BackキーでTitleに戻る or Returnキーでもう一度プレイする");
}
