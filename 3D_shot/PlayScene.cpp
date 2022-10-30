#include "PlayScene.h"
#include "DxLib.h"
#include "Common.h"
#include "Camera.h"
#include "Player.h"
#include "Meteorite.h"
#include "MeteoriteManager.h"
#include "HitChecker.h"
#include "Evaluation.h"
#include "Explosion.h"
#include "SceneManager.h"


//デバック用
#define LINE_AREA_SIZE		10000.0f	// ラインを描く範囲
#define LINE_NUM			50			// ラインの数

const int PlayScene::GAMETIME = 5;		//ゲーム時間

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

void PlayScene::Initialize()
{
	//ゲーム背景
	gameBackGround = LoadGraph("data/image/GameBackground.png");

	camera = new Camera();

	player = new Player();

	hitchecker = new HitChecker();

	explosion = new Explosion();

	evaluation = new Evaluation();

	//隕石マネージャー初期化
	//MeteoriteManager::Initialize();

	//プレイヤー初期化
	player->Initialize();

	//爆発エフェクト初期化
	explosion->Initialize();

	//カメラ初期化
	camera->Initialize();

	//評価UI初期化
	evaluation->Initialize();
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
}

void PlayScene::Activate()
{
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
	

	//デバック用
	{
		int i;
		VECTOR Pos1;
		VECTOR Pos2;

		SetUseZBufferFlag(TRUE);

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
		for (i = 0; i <= LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.x += LINE_AREA_SIZE / LINE_NUM;
			Pos2.x += LINE_AREA_SIZE / LINE_NUM;
		}

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		for (i = 0; i < LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.z += LINE_AREA_SIZE / LINE_NUM;
			Pos2.z += LINE_AREA_SIZE / LINE_NUM;
		}

		SetUseZBufferFlag(FALSE);
	}


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