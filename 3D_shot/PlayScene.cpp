#include "PlayScene.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "Common.h"
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

const int PlayScene::GAMETIME = 21;		//ゲーム時間

PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, frame(0)
		, camera(nullptr)
		, light(nullptr)
		, background(nullptr)
		, field(nullptr)
		, hitChecker(nullptr)
		, uiManager()
		, player(nullptr)
		, explosion(nullptr)
		, evaluation(nullptr)
		, scoreearn(nullptr)
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
		, a(240.0f)
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
	background = new BackGround();
	background->Initialize();

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
	scoreearn = new ScoreEarn();
}

//終了処理
void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(player);
	player->Finalize();

	for (auto ptr : meteorite)
	{
		SafeDelete(ptr);
		ptr->Finalize();
	}
	
	SafeDelete(background);
	background->Finalize();

	SafeDelete(field);
	field->Finalize();

	SafeDelete(hitChecker);

	SafeDelete(uiManager);
	uiManager->Finalize();
	
	SafeDelete(explosion);
	explosion->Finalize();

	SafeDelete(evaluation);
	evaluation->Finalize();

	SafeDelete(scoreearn);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

void PlayScene::Activate()
{
	state = START;
	frame = 0;

	font = CreateFontToHandle("Oranienbaum", 80, 1);
	
	pUpdate = &PlayScene::UpdateStart;
	
	background->Activate();

	field->Activate();

	evaluation->Activate();

	explosion->Activate();
	
	player->Activate();
}

//ゲーム時間計算
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

//隕石を登録
void PlayScene::EntryMeteorite(Meteorite* newMeteorite)
{
	meteorite.emplace_back(newMeteorite);
}

//隕石を削除
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

//隕石の出現間隔
void PlayScene::MeteoritePop(float deltaTime)
{
	meteoritePopCount += deltaTime;

	if (countDown > 65)
	{
		if (meteoritePopCount > 1.2f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
		}
	}
	if (countDown < 64)
	{
		if (meteoritePopCount > 1.0f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
		}
	}
	if (countDown < 50)
	{
		if (meteoritePopCount > 0.8f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
		}
	}
	if (countDown < 30)
	{
		if (meteoritePopCount > 0.5f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
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
}

void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}

	++frame;
}

//ゲーム開始前
void PlayScene::UpdateStart(float deltaTime)
{
	//if (frame > 10)
	{
		frame = 0;
		score = 0;
		state = GAME;
		
		pUpdate = &PlayScene::UpdateGame;

		Score::GetInstance().Activate();

		scoreearn->Activate();

		TimeSlow::GetInstance().SetTimeSlow(slow);

		//for (auto ptr : meteorite)
		//{
		//	//隕石活性化
		//	ptr->Activate();
		//}
		
		//ゲーム起動時の時間を取得
		startTime = GetNowCount();
	}
}

//ゲーム中
void PlayScene::UpdateGame(float deltaTime)
{
	//プレイヤーの制御
	player->Update(deltaTime);

	//隕石の出現間隔
	MeteoritePop(deltaTime);
	
	for (auto ptr : meteorite)
	{
		//隕石制御
		ptr->Update(deltaTime, player);

		//制限時間が11秒以下になったらフィーバー状態へ移行
		if (countDown < 20)
		{
			ptr->BlueColor();
		}
		if (countDown < 11)
		{
			state = FEVER;
			ptr->SpeedUp();
			ptr->RedColor();
			pUpdate = &PlayScene::UpdateFever;
		}
		if (countDown == 0)
		{
			DeleteMeteorite(ptr);
		}

		//プレイヤーと隕石の当たり判定
		hitChecker->PlayerAndMeteorite(player, ptr, explosion, evaluation, scoreearn);

		//隕石と衝突したもしくは制限時間が0になったら
		if (hitChecker->Hit())
		{
			DeleteMeteorite(ptr);
		}
		
	}

	//スコアを計算
	Score::GetInstance().Scoring();

	//スコアを取得
	score = Score::GetInstance().GetScore();

	GameCountDown();
}

//フィーバー中
void PlayScene::UpdateFever(float deltaTime)
{
	UpdateGame(deltaTime);
	/*a -= tan(10.0f);*/
}

void PlayScene::Draw()
{
	//背景描画
	background->Draw();

	//評価UIの描画
	evaluation->Draw();

	//プレイヤー描画
	player->Draw();

	for (auto ptr : meteorite)
	{
		//隕石描画
		ptr->Draw();
	}

	//フィールド描画
	field->Draw();

	//爆発エフェクト描画
	explosion->Draw();

	//UI管理クラスの描画
	uiManager->Draw(state, frame);

	//制限時間表示
	DrawFormatStringToHandle(500, 100, GetColor(255, 0, 0), font, "TIME : %d", countDown);

	//獲得スコア表示
	DrawFormatStringToHandle(1000, 100, GetColor(255, 255, 0), font, "SCORE : %d", score);
	
	//DrawBillboard3D(VGet(320.0f, a, 10.0f), 0.5f, 0.5f, 50.0f, 0.0f, star, TRUE);
}