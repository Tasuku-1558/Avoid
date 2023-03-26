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
#include "Score.h"
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
	, targetScore(0)
	, wave(0)
	, shadowMapHandle(0)
	, frame(0.0f)
	, meteoritePopCount(0.0f)
	, slow(false)
	, pUpdate(nullptr)
	, GAME_TIME(20)
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

	//シャドウマップの削除
	DeleteShadowMap(shadowMapHandle);
}

/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize()
{
	camera = new Camera();

	/*light = new Light();
	light->GameLight();*/

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

	//シャドウマップハンドルの作成
	shadowMapHandle = MakeShadowMap(SCREEN_WIDTH, SCREEN_HEIGHT);

	//シャドウマップが想定するライトの方向をセット
	SetShadowMapLightDirection(shadowMapHandle, LIGHT_DIRECTION);

	//シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(shadowMapHandle, SHADOWMAP_MINPOSITION, SHADOUMAP_MAXPOSITION);

	pUpdate = &GameScene::UpdateStart;
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
		/*gameState = GameState::RESULT;
		pUpdate = &GameScene::UpdateResult;*/

		nowSceneType = SceneType::RESULT;
	}
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
	Score::GetInstance().Activate();

	TimeSlow::GetInstance().SetTimeSlow(slow);

	//ゲーム起動時の時間を取得
	startTime = GetNowCount();

	gameState = GameState::GAME;
	pUpdate = &GameScene::UpdateWave1;
}

/// <summary>
/// Wave1
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateWave1(float deltaTime)
{
	backGround->Update();

	player->Update(deltaTime);

	//隕石の出現間隔
	MeteoritePop(deltaTime);
	
	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Update(deltaTime);

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
			pUpdate = &GameScene::UpdateFinal;
		}

		//隕石と衝突したもしくは制限時間が0になったら隕石を消す
		if (hitChecker->Hit() || countDown == 0)
		{
			DeleteMeteorite(meteoritePtr);
		}
	}

	//プレイヤーと隕石の衝突判定
	hitChecker->PlayerAndMeteorite(player, &meteorite, scoreEarn);

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
void GameScene::UpdateFinal(float deltaTime)
{
	UpdateWave1(deltaTime);
}

void GameScene::GameFinish(float deltaTime)
{
}

/// <summary>
/// 結果画面
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateResult(float deltaTime)
{
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	backGround->Draw();

	field->Draw();

	//シャドウマップへの描画の準備
	ShadowMap_DrawSetup(shadowMapHandle);

	player->Draw();

	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Draw();
	}

	//シャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	//描画に使用するシャドウマップを設定
	SetUseShadowMap(0, shadowMapHandle);

	player->Draw();

	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Draw();
	}

	//描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);

	effectManager->Draw();

	evaluation->Draw();

	uiManager->Draw(gameState, font, countDown, score, wave);

	if (gameState == GameState::RESULT || gameState == GameState::FINISH)
	{
		fadeManager->Draw();
	}
}