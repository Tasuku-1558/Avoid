#include "GameScene.h"

#include "PreCompiledHeader.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Field.h"
#include "Player.h"
#include "Meteorite.h"
#include "HitChecker.h"
#include "UiManager.h"
#include "Evaluation.h"
#include "ScoreEarn.h"
#include "EffectManager.h"
#include "FadeManager.h"
#include "SoundManager.h"
#include "TimeSlow.h"


/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
	: SceneBase(SceneType::GAME)
	, gameState(GameState::START)
	, meteorite()
	, startTime(0)
	, nowTime(0)
	, countDown(0)
	, score(0)
	, font(0)
	, wave(0)
	, excellentCount(0)
	, greatCount(0)
	, goodCount(0)
	, missCount(0)
	, frame(0.0f)
	, meteoritePopCount(0.0f)
	, pUpdate(nullptr)
	, GAME_TIME(5)
	, displayCount(0.0f)
	, scoreFont(0)
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	for (auto meteoritePtr : meteorite)
	{
		DeleteMeteorite(meteoritePtr);
	}

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize()
{
	camera = new Camera();

	light = new Light();
	light->GameLight();

	backGround = new BackGround();

	field = new Field();

	player = new Player();

	effectManager = new EffectManager();

	evaluation = new Evaluation();

	hitChecker = new HitChecker(effectManager, evaluation);

	uiManager = new UiManager();

	scoreEarn = new ScoreEarn();

	fadeManager = new FadeManager();

	font = CreateFontToHandle("Oranienbaum", 80, 1);
	scoreFont = CreateFontToHandle("Oranienbaum", 130, 1);

	//ゲーム起動時の時間を取得
	startTime = GetNowCount();

	//ゲームBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::GAME);

	pUpdate = &GameScene::UpdateStart;
}

/// <summary>
/// 隕石を登録
/// </summary>
/// <param name="newMeteorite"></param>
void GameScene::EntryMeteorite(Meteorite* newMeteorite)
{
	meteorite.emplace_back(newMeteorite);
}

/// <summary>
/// 隕石を削除
/// </summary>
/// <param name="deleteMeteorite"></param>
void GameScene::DeleteMeteorite(Meteorite* deleteMeteorite)
{
	//隕石オブジェクトから検索して削除
	auto iter = std::find(meteorite.begin(), meteorite.end(), deleteMeteorite);

	if (iter != meteorite.end())
	{
		//隕石オブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, meteorite.end() - 1);
		meteorite.pop_back();

		return;
	}
}

/// <summary>
/// 隕石の出現間隔
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::MeteoritePop(float deltaTime)
{
	meteoritePopCount += deltaTime;

	if (meteoritePopCount > 1.2f)
	{
		Meteorite* newMeteorite = new Meteorite(player);
		EntryMeteorite(newMeteorite);
		meteoritePopCount = 0.0f;
		wave = 1;
	}
}

/// <summary>
/// スコアを取得
/// </summary>
void GameScene::GetScore()
{
	score		   = scoreEarn->GetScore();
	excellentCount = scoreEarn->GetExcellentCount();
	greatCount	   = scoreEarn->GetGreatCount();
	goodCount	   = scoreEarn->GetGoodCount();
	missCount	   = scoreEarn->GetMissCount();

	//スコアを計算
	scoreEarn->Update();
}

/// <summary>
/// ゲーム時間計算
/// </summary>
void GameScene::GameCountDown()
{
	nowTime = GetNowCount();
	countDown = GAME_TIME - (nowTime - startTime) / 1000;

	//制限時間が0になったら
	if (countDown == 0)
	{
		gameState = GameState::FINISH;
		pUpdate = &GameScene::UpdateFinish;
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
SceneType GameScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新

		return nowSceneType;
	}
}

/// <summary>
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateStart(float deltaTime)
{
	gameState = GameState::GAME;
	pUpdate = &GameScene::UpdateGame;
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateGame(float deltaTime)
{
	backGround->Update();

	player->Update(deltaTime);

	//隕石の出現間隔
	MeteoritePop(deltaTime);
	
	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Update(deltaTime);

		//隕石と衝突したもしくは制限時間が0になったら隕石を消す
		if (hitChecker->Hit() || countDown == 0)
		{
			DeleteMeteorite(meteoritePtr);
		}
	}

	//プレイヤーと隕石の衝突判定
	hitChecker->PlayerAndMeteorite(player, &meteorite, scoreEarn);

	//スコアを取得
	GetScore();

	GameCountDown();
}

/// <summary>
/// ゲーム終了
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateFinish(float deltaTime)
{
	frame += deltaTime;

	//ゲームBGMを停止
	SoundManager::GetInstance().StopBgm();

	TimeSlow::GetInstance().SetTimeSlow(false);

	if (frame > 1.0f)
	{
		fadeManager->FadeMove();
	}

	//フレーム数が3.2秒経過したら
	if (frame > 3.2f)
	{
		gameState = GameState::RESULT;
		pUpdate = &GameScene::UpdateResult;
	}
}

/// <summary>
/// 結果画面
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateResult(float deltaTime)
{
	backGround->Update();

	//リザルトBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::RESULT);

	//タイトル画面へ
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		//リザルトBGMを停止
		SoundManager::GetInstance().StopBgm();

		nowSceneType = SceneType::TITLE;
	}

	if (CheckHitKey(KEY_INPUT_G))
	{
		Initialize();

		gameState = GameState::START;
		pUpdate = &GameScene::UpdateStart;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	backGround->Draw();

	if (gameState != GameState::RESULT)
	{
		evaluation->Draw();

		field->Draw();

		player->Draw();

		for (auto meteoritePtr : meteorite)
		{
			meteoritePtr->Draw();
		}

		effectManager->Draw();

		uiManager->Draw(gameState, font, countDown, score, wave);
	}

	if (gameState == GameState::FINISH)
	{
		fadeManager->Draw();
	}

	//リザルト画面の表示
	if (gameState == GameState::RESULT)
	{
		DrawResult();
	}
}

void GameScene::DrawResult()
{
	displayCount ++;

	if (displayCount > 10.0f)
	{
		DrawFormatStringToHandle(650, 250, GetColor(255, 69, 0), scoreFont, "SCORE : %d", score);

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