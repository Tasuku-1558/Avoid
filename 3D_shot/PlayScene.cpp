#include "PlayScene.h"
#include "DxLib.h"
#include "Common.h"
#include "Camera.h"
#include "Player.h"
#include "Meteorite.h"
#include "MeteoriteManager.h"
#include "HitChecker.h"
#include "Evaluation.h"
#include "EarnScore.h"
#include "Explosion.h"
#include "SceneManager.h"


const int PlayScene::GAMETIME = 30;		//ゲーム時間

PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, camera(nullptr)
		, hitchecker(nullptr)
		, player(nullptr)
		, explosion(nullptr)
		, evaluation(nullptr)
		, earnscore(nullptr)
		, pUpdate(nullptr)
		, meteoriteManager(nullptr)
		, meteorite()
		, meteoritePopFlag(false)
		, startTime(0)
		, nowTime(0)
		, countDown(0)
		, gameBackGround(0)
		, score(0)
		, targetScore(0)
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
	//ゲーム背景
	gameBackGround = LoadGraph("data/image/GameBackground.png");

	//カメラクラス
	camera = new Camera();
	camera->Initialize();

	//プレイヤークラス
	player = new Player();
	player->Initialize();

	//当たり判定クラス
	hitchecker = new HitChecker();

	//爆発エフェクトクラス
	explosion = new Explosion();
	explosion->Initialize();

	//評価UIクラス
	evaluation = new Evaluation();
	evaluation->Initialize();

	//スコアクラス
	earnscore = new EarnScore();
	
	//MeteoriteManager::Initialize();
}

void PlayScene::Finalize()
{
	//ゲーム背景を解放
	DeleteGraph(gameBackGround);

	//カメラを解放
	SafeDelete(camera);

	//プレイヤーを解放
	SafeDelete(player);

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//隕石を解放
			SafeDelete(meteorite[i]);
		}
	}
	
	//隕石マネージャーを解放
	//MeteoriteManager::Finalize();
	
	//ヒットチェッカーを解放
	SafeDelete(hitchecker);
	
	//爆発エフェクトを解放
	SafeDelete(explosion);
	explosion->Finalize();

	//評価UIを解放
	SafeDelete(evaluation);
	evaluation->Finalize();

	SafeDelete(earnscore);
}

void PlayScene::Activate()
{
	state = START;
	pUpdate = &PlayScene::UpdateStart;

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		//隕石生成
		meteorite[i] = new Meteorite();

		if (meteorite[i] != nullptr)
		{
			//隕石初期化
			meteorite[i]->Initialize();

			//隕石活性化
			meteorite[i]->Activate();
		}
	}
	
	
	//Meteorite* me = new Meteorite;

	////隕石活性化
	//me->Activate();
	//MeteoriteManager::Entry(me);

	earnscore->Activate();

	//プレイヤー活性化
	player->Activate();

	//ゲーム起動時の時間を取得
	startTime = GetNowCount();
}


void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		//状態ごとに更新
	}

	//プレイヤーの制御
	player->Update(deltaTime);

	meteoritePopFlag = true;

	for (/*auto ptr:meteorite*/int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//隕石出現フラグがtrueの時
			if (meteoritePopFlag)
			{
				meteoritePopFlag = false;

				//隕石制御
				meteorite[i]->Update(deltaTime, player);


				//隕石マネージャー制御
				//MeteoriteManager::Update(deltaTime, player);

				//プレイヤーと隕石の当たり判定
				hitchecker->PlayerAndMeteorite(player, /*ptr*/meteorite, meteoriteManager, explosion, evaluation, earnscore);
			}
		}
	}
}

void PlayScene::UpdateStart()
{
	state = GAME;
	pUpdate = &PlayScene::UpdateGame;
}

void PlayScene::UpdateGame()
{
	//HitCheckerのスコアを取得
	targetScore = earnscore->GetScore();

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

	nowTime = GetNowCount();
	countDown = GAMETIME - (nowTime - startTime) / 1000;

	//制限時間が0になったら
	if (countDown == 0)
	{
		parent->SetNextScene(SceneManager::RESULT);
		return;
	}
}

void PlayScene::Draw()
{
	//ゲーム背景描画
	DrawBillboard3D(VGet(0.0f, 300.0f, 1200.0f), 0.5f, 0.5f, 4000.0f, 0.0f, gameBackGround, TRUE);

	//プレイヤー描画
	player->Draw();

	//爆発エフェクト描画
	explosion->Draw();

	//評価UIの描画
	evaluation->Draw();

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//隕石描画
			meteorite[i]->Draw();
		}
	}

	//隕石マネージャー描画
	//MeteoriteManager::Draw();


	SetFontSize(80);			//文字のフォントサイズ変更
	ChangeFont("ＭＳ 明朝");	//種類をMS明朝に変更

	//制限時間表示
	DrawFormatString(500, 100, GetColor(255, 0, 0), "TIME : %d", countDown);

	//獲得スコア表示
	DrawFormatString(1000, 100, GetColor(255, 255, 0), "SCORE : %d", score);
}