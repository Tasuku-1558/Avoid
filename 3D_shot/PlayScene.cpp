#include "PlayScene.h"
#include "Common.h"
#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
#include "Meteorite.h"
#include "MeteoriteManager.h"
#include "HitChecker.h"
#include "Evaluation.h"
#include "Explosion.h"
#include "SceneManager.h"


const int PlayScene::GAMETIME = 60;		//ゲーム時間

PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, camera(nullptr)
		, hitchecker(nullptr)
		, player(nullptr)
		, explosion(nullptr)
		, evaluation(nullptr)
		, meteorite()
		, meteoritePopFlag(false)
		, startTime(0)
		, nowTime(0)
		, countDown(0)
		, gameBackground(0)
		, score(0)
		, targetScore(0)
{
	//処理なし
}

PlayScene::~PlayScene()
{
	//処理なし
}

void PlayScene::Initialize()
{
	//ゲーム画面背景
	gameBackground = LoadGraph("data/Image/GameBackground.png");

	camera = new Camera();

	player = new Player();

	hitchecker = new HitChecker();

	explosion = new Explosion();

	evaluation = new Evaluation();

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		//隕石生成
		meteorite[i] = new Meteorite();

		if (meteorite[i] != nullptr)
		{
			//隕石初期化
			meteorite[i]->Initialize();
		}
	}
	
	//隕石マネージャー初期化
	//MeteoriteManager::Initialize();

	//プレイヤー初期化
	player->Initialize();

	//エフェクト初期化
	explosion->Initialize();

	//カメラ初期化
	camera->Initialize();

	//評価UI初期化
	evaluation->Initialize();
}

void PlayScene::Finalize()
{
	//ゲーム画面背景を解放
	DeleteGraph(gameBackground);

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
	
	SafeDelete(explosion);

	//評価UIの解放
	SafeDelete(evaluation);
}

void PlayScene::Activate()
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//隕石活性化
			meteorite[i]->Activate();
		}
		
	}
	
	//for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	//{
	//	Meteorite* me = new Meteorite;

	//	//隕石活性化
	//	me->Activate();
	//	MeteoriteManager::Entry(me);
	//}
	

	//プレイヤー活性化
	player->Activate();

	//ゲーム起動時の時間を取得
	startTime = GetNowCount();

	hitchecker->Initialize();
}


void PlayScene::Update(float deltaTime)
{
	//プレイヤーの制御
	player->Update(deltaTime);

	meteoritePopFlag = true;
	
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//隕石出現フラグがtrueの時
			if (meteoritePopFlag)
			{
				meteoritePopFlag = false;
				
				
				//隕石制御
				meteorite[i]->Update(deltaTime, player);
				
				////隕石マネージャー制御
				//MeteoriteManager::Update(deltaTime, player);

				//プレイヤーと隕石の当たり判定
				hitchecker->PlayerAndMeteorite(player, meteorite, meteoriteManager, explosion, evaluation);

			}
		}
	}
	

	//デバック用
	x = player->GetPosition().x;
	y = player->GetPosition().y;
	Direction = hitchecker->GetDirection();

	//HitCheckerのスコアを取得
	targetScore = hitchecker->GetScore();

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
	//ゲーム画面背景描画
	DrawBillboard3D(VGet(0.0f, 300.0f, 1200.0f), 0.5f, 0.5f, 4000.0f, 0.0f, gameBackground, TRUE);

	//プレイヤー描画
	player->Draw();

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
	
	SetFontSize(60);			//文字のフォントサイズ変更
	ChangeFont("ＭＳ 明朝");	//種類をMS明朝に変更

	//制限時間表示
	DrawFormatString(800, 100, GetColor(255, 0, 0), "TIME : %d", countDown);

	//獲得スコア表示
	DrawFormatString(800, 150, GetColor(255, 255, 0), "SCORE : %d", score);

	//デバック用
	DrawFormatString(500, 300, GetColor(255, 0, 0), "x : %d", x);
	DrawFormatString(500, 350, GetColor(255, 0, 0), "y : %d", y);
	DrawFormatString(500, 400, GetColor(255, 0, 0), "Direction : %f", Direction);
}