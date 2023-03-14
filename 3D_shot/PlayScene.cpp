#include "PlayScene.h"
#include "DxLib.h"

#include "SceneManager.h"
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
#include "Explosion.h"
#include "Score.h"
#include "TimeSlow.h"

const int PlayScene::GAMETIME = 90;		//ゲーム時間

PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, frame(0.0f)
		, camera(nullptr)
		, light(nullptr)
		, backGround(nullptr)
		, field(nullptr)
		, hitChecker(nullptr)
		, uiManager()
		, player(nullptr)
		, explosion(nullptr)
		, evaluation(nullptr)
		, scorEearn(nullptr)
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
{
	//処理なし
}

PlayScene::~PlayScene()
{
	//処理なし
}

//初期化処理
void PlayScene::Initialize()
{
	//カメラクラス
	camera = new Camera();
	camera->Initialize();

	//ライトクラス
	light = new Light();
	light->Initialize();

	//プレイヤークラス
	player = new Player();
	player->Initialize();

	//背景クラス
	backGround = new BackGround();
	backGround->Initialize();

	//フィールドクラス
	field = new Field();
	field->Initialize();

	//当たり判定クラス
	hitChecker = new HitChecker();

	//UI画像管理クラス
	uiManager = new UiManager();
	uiManager->Initialize();

	//爆発エフェクトクラス
	explosion = new Explosion();
	explosion->Initialize();

	//評価UIクラス
	evaluation = new Evaluation();
	evaluation->Initialize();

	//スコア獲得クラス
	scorEearn = new ScoreEarn();
}

//終了処理
void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(player);

	for (auto meteoritePtr : meteorite)
	{
		SafeDelete(meteoritePtr);
	}
	
	SafeDelete(backGround);

	SafeDelete(field);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);
	
	SafeDelete(explosion);

	SafeDelete(evaluation);

	SafeDelete(scorEearn);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

void PlayScene::Activate()
{
	state = State::START;
	pUpdate = &PlayScene::UpdateStart;

	frame = 0.0f;
	wave = 0;
	countDown = 0;

	font = CreateFontToHandle("Oranienbaum", 80, 1);
	
	backGround->Activate();

	field->Activate();

	evaluation->Activate();

	explosion->Activate();
	
	player->Activate();
}

/// <summary>
/// ゲーム時間計算
/// </summary>
void PlayScene::GameCountDown()
{
	nowTime = GetNowCount();
	countDown = GAMETIME - (nowTime - startTime) / 1000;

	//制限時間が0になったら
	if (countDown == 0)
	{
		parent->SetNextScene(SceneManager::RESULT);
		return;
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
void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}
}

/// <summary>
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateStart(float deltaTime)
{
	state = State::GAME;
	pUpdate = &PlayScene::UpdateGame;

	Score::GetInstance().Activate();

	scorEearn->Activate();

	TimeSlow::GetInstance().SetTimeSlow(slow);

	for (auto meteoritePtr : meteorite)
	{
		//隕石活性化
		meteoritePtr->Activate();
	}

	//ゲーム起動時の時間を取得
	startTime = GetNowCount();
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateGame(float deltaTime)
{
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
			state = State::FINALWAVE;
			meteoritePtr->SpeedUp();
			meteoritePtr->ChangeColor(5.0f, 0.0f, 0.0f);
			wave = 5;
			pUpdate = &PlayScene::UpdateFever;
		}

		//プレイヤーと隕石の当たり判定
		hitChecker->PlayerAndMeteorite(player, meteoritePtr, explosion, evaluation, scorEearn);

		//隕石と衝突したもしくは制限時間が0になったら隕石を消す
		if (hitChecker->Hit() || countDown == 0)
		{
			DeleteMeteorite(meteoritePtr);
		}
	}

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
void PlayScene::UpdateFever(float deltaTime)
{
	UpdateGame(deltaTime);
}

/// <summary>
/// 描画処理
/// </summary>
void PlayScene::Draw()
{
	backGround->Draw();

	evaluation->Draw();

	player->Draw();

	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Draw();
	}

	field->Draw();

	explosion->Draw();

	uiManager->Draw(state, frame, font, countDown, score, wave);
}