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
#include "ResultUi.h"

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
	, excellentCount(0)
	, greatCount(0)
	, goodCount(0)
	, missCount(0)
	, scoreFont(0)
	, fontHandle(0)
	, wave(0)
	, frame(0.0f)
	, meteoritePopCount(0.0f)
	, sceneChangeTitle(false)
	, sceneChangeGame(false)
	, pUpdate(nullptr)
	, GAME_TIME(82)
	, METEORITE_POP_CATEGORY(5)
	, GAME_START_COUNT(3.0f)
	, FADE_START_COUNT(1.0f)
	, a(false)
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	//作成したフォントデータの削除
	DeleteFontToHandle(scoreFont);
	DeleteFontToHandle(fontHandle);
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

	resultUi = new ResultUi();

	//フォントの生成
	scoreFont = CreateFontToHandle("Oranienbaum", 130, 1);
	fontHandle = CreateFontToHandle("Oranienbaum", 80, 1);

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

	Pop pop[] =
	{
		{90,80,1.2f,1},
		{80,60,1.0f,2},
		{60,40,0.7f,3},
		{40,20,0.9f,4},
		{20, 0,0.7f,5},
	};

	for (int i = 0; i < METEORITE_POP_CATEGORY; i++)
	{
		if (countDown < pop[i].sTime && countDown > pop[i].eTime && meteoritePopCount > pop[i].popCount)
		{
			Meteorite* newMeteorite = new Meteorite(player);
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			wave = pop[i].wave;
		}
	}
}

/// <summary>
/// ゲーム時間計算
/// </summary>
void GameScene::GameCountDown()
{
	if (!a)
	{
		nowTime = GetNowCount();
		countDown = GAME_TIME - (nowTime - startTime) / 1000;
	}

	if (countDown <= 80)
	{
		countDown = 80;

		a = true;

		nowTime = GetNowCount();

		if (CheckHitKey(KEY_INPUT_J))
		{
			startTime = GetNowCount();
			countDown = 80 - (nowTime - startTime) / 1000;
		}
	}

	//制限時間が0になったら
	if (countDown == 0)
	{
		gameState = GameState::FINISH;
		pUpdate = &GameScene::UpdateFinish;
	}
}

void GameScene::ResultScore()
{
	//スコアを計算
	scoreEarn->Update();

	//スコアを取得
	score = scoreEarn->GetScore();
	excellentCount = scoreEarn->GetExcellentCount();
	greatCount = scoreEarn->GetGreatCount();
	goodCount = scoreEarn->GetGoodCount();
	missCount = scoreEarn->GetMissCount();
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
	frame += deltaTime;

	player->Update(deltaTime);

	//3秒経過したら
	if (frame > GAME_START_COUNT)
	{
		//ゲーム起動時の時間を取得
		startTime = GetNowCount();

		//ゲームBGMを再生
		SoundManager::GetInstance().PlayBgm(SoundManager::GAME);

		gameState = GameState::GAME;
		pUpdate = &GameScene::UpdateGame;
	}
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

		if (wave == 5)
		{
			meteoritePtr->SpeedUp();
		}

		//隕石と衝突したもしくは制限時間が0になったら隕石を消す
		if (hitChecker->Hit() || countDown == 0)
		{
			DeleteMeteorite(meteoritePtr);
		}
	}

	hitChecker->PlayerAndMeteorite(player, &meteorite, scoreEarn);

	ResultScore();

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

	//1秒経過したら
	if (frame > FADE_START_COUNT)
	{
		fadeManager->FadeMove();
	}

	//フェードが終わったら
	if (fadeManager->FadeEnd())
	{
		gameState = GameState::RESULT;
		pUpdate = &GameScene::UpdateResult;

		fadeManager->FadeReset();
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

	if (CheckHitKey(KEY_INPUT_BACK))
	{
		sceneChangeTitle = true;
	}

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		sceneChangeGame = true;
	}

	if (sceneChangeTitle)
	{
		fadeManager->FadeMove();

		//リザルトBGMを停止
		SoundManager::GetInstance().StopBgm();

		//フェードが終わったら
		if (fadeManager->FadeEnd())
		{
			//タイトル画面へ
			nowSceneType = SceneType::TITLE;
		}
	}

	if (sceneChangeGame)
	{
		fadeManager->FadeMove();

		//リザルトBGMを停止
		SoundManager::GetInstance().StopBgm();

		//フェードが終わったら
		if (fadeManager->FadeEnd())
		{
			//もう一度プレイする
			gameState = GameState::START;
			Initialize();

			frame = 0.0f;

			sceneChangeGame = false;
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	backGround->Draw();

	evaluation->Draw();

	if (gameState != GameState::RESULT && gameState != GameState::START)
	{
		field->Draw();

		player->Draw();

		for (auto meteoritePtr : meteorite)
		{
			meteoritePtr->Draw();
		}
	}

	effectManager->Draw();

	uiManager->Draw(gameState, frame, fontHandle, countDown, score, wave);

	if (gameState == GameState::RESULT)
	{
		resultUi->Draw(scoreFont, fontHandle, score, excellentCount, greatCount, goodCount, missCount);
	}

	if (gameState == GameState::FINISH || gameState == GameState::RESULT)
	{
		fadeManager->Draw();
	}
}