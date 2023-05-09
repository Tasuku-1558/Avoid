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
	, gameTime(90)
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
	, countDownStop(false)
	, pUpdate(nullptr)
	, STOP_TIME_CATEGORY(4)
	, TIME_DIVISION(1000)
	, METEORITE_POP_CATEGORY(5)
	, SCORE_FONT_SIZE(130)
	, FONT_SIZE(80)
	, FONT_THICK(1)
	, GAME_FINISH_TIME(0)
	, WAVE1_POP_START_TIME(90)
	, WAVE2_POP_START_TIME(80)
	, WAVE3_POP_START_TIME(60)
	, WAVE4_POP_START_TIME(40)
	, WAVE5_POP_START_TIME(20)
	, WAVE1_POP_END_TIME(80)
	, WAVE2_POP_END_TIME(60)
	, WAVE3_POP_END_TIME(40)
	, WAVE4_POP_END_TIME(20)
	, WAVE5_POP_END_TIME(0)
	, WAVE1(1)
	, WAVE2(2)
	, WAVE3(3)
	, WAVE4(4)
	, WAVE5(5)
	, WAVE2_STOP_TIME(80)
	, WAVE3_STOP_TIME(60)
	, WAVE4_STOP_TIME(40)
	, WAVE5_STOP_TIME(20)
	, WAVE2_RELEASE_TIME(79)
	, WAVE3_RELEASE_TIME(59)
	, WAVE4_RELEASE_TIME(39)
	, WAVE5_RELEASE_TIME(19)
	, WAVE1_POP_COUNT(1.2f)
	, WAVE2_POP_COUNT(1.0f)
	, WAVE3_POP_COUNT(0.7f)
	, WAVE4_POP_COUNT(0.9f)
	, WAVE5_POP_COUNT(0.7f)
	, INITIAL_METEORITE_POP_COUNT(0.0f)
	, GAME_START_COUNT(3.0f)
	, FADE_START_COUNT(1.0f)
	, INITIAL_FRAME(0.0f)
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

	light = new Light(Light::LightType::GAME_LIGHT);

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
	scoreFont = CreateFontToHandle("Oranienbaum", SCORE_FONT_SIZE, FONT_THICK);
	fontHandle = CreateFontToHandle("Oranienbaum", FONT_SIZE, FONT_THICK);

	pUpdate = &GameScene::UpdateStart;
}

/// <summary>
/// 隕石の出現間隔
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void GameScene::MeteoritePop(float deltaTime)
{
	meteoritePopCount += deltaTime;

	Pop pop[] =
	{
		{WAVE1_POP_START_TIME, WAVE1_POP_END_TIME, WAVE1_POP_COUNT, WAVE1},
		{WAVE2_POP_START_TIME, WAVE2_POP_END_TIME, WAVE2_POP_COUNT, WAVE2},
		{WAVE3_POP_START_TIME, WAVE3_POP_END_TIME, WAVE3_POP_COUNT, WAVE3},
		{WAVE4_POP_START_TIME, WAVE4_POP_END_TIME, WAVE4_POP_COUNT, WAVE4},
		{WAVE5_POP_START_TIME, WAVE5_POP_END_TIME, WAVE5_POP_COUNT, WAVE5},
	};

	for (int i = 0; i < METEORITE_POP_CATEGORY; i++)
	{
		if (countDown < pop[i].popStartTime && countDown > pop[i].popEndTime && meteoritePopCount > pop[i].popCount)
		{
			activeMeteorite.emplace_back(new Meteorite(player->GetPosition()));

			meteoritePopCount = INITIAL_METEORITE_POP_COUNT;
			wave = pop[i].wave;
		}
	}
}

/// <summary>
/// ゲーム時間計算
/// </summary>
void GameScene::GameCountDown()
{
	//現在の時間を取得
	nowTime = GetNowCount();

	if (!countDownStop)
	{
		countDown = gameTime - (nowTime - startTime) / TIME_DIVISION;
	}

	Time time[] =
	{
		{WAVE2_STOP_TIME, WAVE2_RELEASE_TIME},
		{WAVE3_STOP_TIME, WAVE3_RELEASE_TIME},
		{WAVE4_STOP_TIME, WAVE4_RELEASE_TIME},
		{WAVE5_STOP_TIME, WAVE5_RELEASE_TIME},
	};

	for (int i = 0; i < STOP_TIME_CATEGORY; i++)
	{
		//制限時間を止める時間になったら
		if (countDown == time[i].stopTime)
		{
			countDown = time[i].stopTime;
			countDownStop = true;

			//ウェーブ画像の透過処理が終わったら
			if (uiManager->AlphaEnd())
			{
				//ゲーム起動時の時間を取得
				startTime = GetNowCount();

				//透過処理の初期化
				uiManager->AlphaReset();

				countDownStop = false;
				gameTime = time[i].releaseTime;
			}
		}
	}

	//制限時間が0になったら
	if (countDown == GAME_FINISH_TIME)
	{
		gameState = GameState::FINISH;
		pUpdate = &GameScene::UpdateFinish;
	}
}

/// <summary>
/// シーン切り替え
/// </summary>
void GameScene::SceneChange()
{
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		sceneChangeTitle = true;
	}

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		sceneChangeGame = true;
	}
}

/// <summary>
/// シーンの入力
/// </summary>
/// <param name="sceneChange">どのシーンに遷移するか</param>
/// <param name="sceneType">シーンの種類</param>
void GameScene::InputScene(bool sceneChange, SceneType sceneType)
{
	if (sceneChange)
	{
		fadeManager->FadeMove();

		//リザルトBGMを停止
		SoundManager::GetInstance().StopBgm();

		//フェードが終わったら
		if (fadeManager->FadeEnd())
		{
			//シーンを変える
			nowSceneType = sceneType;

			//ゲームシーンに遷移するならば初期化処理を行う
			if (sceneChange == sceneChangeGame)
			{
				gameState = GameState::START;
				Initialize();

				frame = INITIAL_FRAME;

				sceneChangeGame = false;
			}
		}
	}
}

/// <summary>
/// 画面を遷移する
/// </summary>
void GameScene::ReturnScreen()
{
	InputScene(sceneChangeTitle, SceneType::TITLE);

	InputScene(sceneChangeGame, SceneType::GAME);
}

/// <summary>
/// リザルト画面用スコア
/// </summary>
void GameScene::ResultScore()
{
	//スコアを計算
	scoreEarn->Update();

	//スコアを取得
	score		   = scoreEarn->GetScore();
	excellentCount = scoreEarn->GetExcellentCount();
	greatCount	   = scoreEarn->GetGreatCount();
	goodCount	   = scoreEarn->GetGoodCount();
	missCount	   = scoreEarn->GetMissCount();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
SceneType GameScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}

	return nowSceneType;
}

/// <summary>
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
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
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void GameScene::UpdateGame(float deltaTime)
{
	backGround->Update();

	player->Update(deltaTime);

	//隕石の出現間隔
	MeteoritePop(deltaTime);
	
	for (auto itr = activeMeteorite.begin(); itr != activeMeteorite.end(); ++itr)
	{
		(*itr)->Update(deltaTime);

		if (wave == WAVE5)
		{
			(*itr)->SpeedUp();
		}

		//隕石と衝突したもしくは制限時間が0になったら隕石を消す
		if (hitChecker->Hit() || countDown == GAME_FINISH_TIME)
		{
			if (itr != activeMeteorite.end())
			{
				std::iter_swap(itr, activeMeteorite.end() - 1);
				activeMeteorite.pop_back();

				return;
			}
		}
	}

	hitChecker->PlayerAndMeteorite(player->GetPosition(), player, &activeMeteorite, scoreEarn);

	ResultScore();

	GameCountDown();
}

/// <summary>
/// ゲーム終了
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
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
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void GameScene::UpdateResult(float deltaTime)
{
	backGround->Update();

	//リザルトBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::RESULT);

	//どのシーンにも遷移していないならば
	if (!sceneChangeTitle && !sceneChangeGame)
	{
		SceneChange();
	}

	ReturnScreen();
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	backGround->Draw();

	evaluation->Draw();

	if (gameState == GameState::GAME || gameState == GameState::FINISH)
	{
		field->Draw();

		player->Draw();

		for (auto itr = activeMeteorite.begin(); itr != activeMeteorite.end(); ++itr)
		{
			(*itr)->Draw();
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