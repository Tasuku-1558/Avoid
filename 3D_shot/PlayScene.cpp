#include "PlayScene.h"

#include "PreCompiledHeader.h"
#include "Player.h"
#include "Meteorite.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Field.h"
#include "HitChecker.h"
#include "UiManager.h"
#include "Evaluation.h"
#include "ScoreEarn.h"
#include "EffectManager.h"
#include "Score.h"
#include "TimeSlow.h"


/// <summary>
/// コンストラクタ
/// </summary>
PlayScene::PlayScene()
	: SceneBase(SceneType::PLAY)
	, gameState(GameState::START)
	, frame(0.0f)
	, pUpdate(nullptr)
	, meteorite()
	, startTime(0)
	, nowTime(0)
	, countDown(0)
	, score(0)
	, font(0)
	, targetScore(0)
	, slow(false)
	, meteoritePopCount(0.0f)
	, wave(0)
	, GAME_TIME(90)
{
	Initialize();
	Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
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
void PlayScene::Initialize()
{
	camera = new Camera();

	light = new Light();

	player = new Player();

	backGround = new BackGround();

	field = new Field();

	effectManager = new EffectManager();

	hitChecker = new HitChecker(effectManager);

	uiManager = new UiManager();

	evaluation = new Evaluation();

	scoreEarn = new ScoreEarn();
}

/// <summary>
/// 活性化処理
/// </summary>
void PlayScene::Activate()
{
	pUpdate = &PlayScene::UpdateStart;

	font = CreateFontToHandle("Oranienbaum", 80, 1);
}

/// <summary>
/// ゲーム時間計算
/// </summary>
void PlayScene::GameCountDown()
{
	nowTime = GetNowCount();
	countDown = GAME_TIME - (nowTime - startTime) / 1000;

	//制限時間が0になったら
	//結果画面へ遷移する
	if (countDown == 0)
	{
		nowSceneType = SceneType::RESULT;
	}
}

/// <summary>
/// 隕石を登録
/// </summary>
/// <param name="newMeteorite"></param>
void PlayScene::EntryMeteorite(Meteorite* newMeteorite)
{
	meteorite.emplace_back(newMeteorite);
}

/// <summary>
/// 隕石を削除
/// </summary>
/// <param name="deleteMeteorite"></param>
void PlayScene::DeleteMeteorite(Meteorite* deleteMeteorite)
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
void PlayScene::MeteoritePop(float deltaTime)
{
	meteoritePopCount += deltaTime;

	if (countDown > 70)
	{
		if (meteoritePopCount > 1.2f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			wave = 1;
		}
	}
	if (countDown < 70)
	{
		if (meteoritePopCount > 0.8f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			wave = 2;
		}
	}
	if (countDown < 50)
	{
		if (meteoritePopCount > 0.5f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			wave = 3;
		}
	}
	if (countDown < 20)
	{
		if (meteoritePopCount > 1.0f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			
		}
	}
	if (countDown < 10)
	{
		if (meteoritePopCount > 1.0f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			
		}
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
SceneType PlayScene::Update(float deltaTime)
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
void PlayScene::UpdateStart(float deltaTime)
{
	gameState = GameState::GAME;
	pUpdate = &PlayScene::UpdateWave1;

	Score::GetInstance().Activate();

	TimeSlow::GetInstance().SetTimeSlow(slow);

	//ゲーム起動時の時間を取得
	startTime = GetNowCount();
}

/// <summary>
/// Wave1
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateWave1(float deltaTime)
{
	backGround->Update();

	player->Update(deltaTime);

	//隕石の出現間隔
	MeteoritePop(deltaTime);
	
	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Update(deltaTime, player);

		//制限時間によって隕石の色やスピードが変化
		if (countDown < 50)
		{
			meteoritePtr->ChangeColor(0.0f, 1.0f, 1.0f);
		}
		if (countDown < 20)
		{
			meteoritePtr->ChangeColor(50.0f, 50.0f, 0.0f);
			wave = 4;
		}
		if (countDown < 11)		//制限時間が11秒以下になったらフィーバー状態へ移行
		{
			gameState = GameState::FINALWAVE;
			meteoritePtr->SpeedUp();
			meteoritePtr->ChangeColor(5.0f, 0.0f, 0.0f);
			wave = 5;
			pUpdate = &PlayScene::UpdateFinal;
		}

		//隕石と衝突したもしくは制限時間が0になったら隕石を消す
		if (hitChecker->Hit() || countDown == 0)
		{
			DeleteMeteorite(meteoritePtr);
		}
	}

	//プレイヤーと隕石の当たり判定
	hitChecker->PlayerAndMeteorite(player, &meteorite, evaluation, scoreEarn);

	//スコアを取得
	score = Score::GetInstance().GetScore();

	//スコアを計算
	Score::GetInstance().Scoring();

	GameCountDown();
}

/// <summary>
/// フィーバー中
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateFinal(float deltaTime)
{
	UpdateWave1(deltaTime);
}

/// <summary>
/// 描画処理
/// </summary>
void PlayScene::Draw()
{
	backGround->Draw();

	evaluation->Draw();

	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Draw();
	}

	field->Draw();

	player->Draw();

	effectManager->Draw();

	uiManager->Draw(gameState, font, countDown, score, wave);
}