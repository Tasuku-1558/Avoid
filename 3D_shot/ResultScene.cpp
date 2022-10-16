#include "ResultScene.h"
#include "DxLib.h"
#include "HitChecker.h"


ResultScene::ResultScene():SceneBase(SceneType::RESULT)
	, hitchecker(new HitChecker())
	, ResultImage(0)
	, ResultBackgroundX(0)
	, ResultBackgroundY(0)
	, Score(0)
{
	//処理なし
}

ResultScene::~ResultScene()
{
	//処理なし
}

void ResultScene::Initialize()
{
	
}

SceneType ResultScene::Update(float deltaTime)
{
	//HitCheckerのスコアを取得
	//Score = hitchecker->GetScore();

	////スコアを目標スコアに足し引きする処理
	//if (TargetScore != Score)
	//{
	//	if (TargetScore > Score)
	//	{
	//		Score += 100;
	//	}
	//	else
	//	{
	//		Score -= 100;
	//	}
	//}

	//次のシーンへ
	//BackキーでTitleSceneへ
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		NowSceneType = SceneType::TITLE;
	}
	//BキーでPlaySceneへ
	else if (CheckHitKey(KEY_INPUT_B))
	{
		NowSceneType = SceneType::PLAY;
	}

	return NowSceneType;
}

void ResultScene::Draw()
{
	//獲得スコア表示
	DrawFormatString(500, 150, GetColor(255, 255, 0), "獲得SCORE : %d", Score);
}
