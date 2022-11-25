#include "PlayScene.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "Common.h"
#include "Player.h"
#include "Meteorite.h"
#include "MeteoriteManager.h"
#include "Camera.h"
#include "BackGround.h"
#include "Field.h"
#include "HitChecker.h"
#include "UiManager.h"
#include "Evaluation.h"
#include "EarnScore.h"
#include "Explosion.h"
#include "Score.h"
#include "TimeSlow.h"

const int PlayScene::GAMETIME = 12;		//ゲーム時間

PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, frame(0)
		, camera(nullptr)
		, background(nullptr)
		, field(nullptr)
		, hitChecker(nullptr)
		, uiManager()
		, player(nullptr)
		, explosion(nullptr)
		, evaluation(nullptr)
		, earnscore(nullptr)
		, pUpdate(nullptr)
		, meteorite()
		, meteoritePopFlag(false)
		, startTime(0)
		, nowTime(0)
		, countDown(0)
		, score(0)
		, font(0)
		, smallFont(0)
		, targetScore(0)
		, slow(false)
		, feverGauge(0.0f)
		, count(0.0f)
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

	//プレイヤークラス
	player = new Player();
	player->Initialize();

	//背景クラス
	background = new BackGround();
	background->Initialize();

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
	earnscore = new EarnScore();
}

void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(player);
	player->Finalize();

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//隕石クラスを解放
			SafeDelete(meteorite[i]);
			meteorite[i]->Finalize();
		}
	}
	
	//for (auto ptr : meteorite)
	//{
	//	//隕石マネージャーを解放
	//	MeteoriteManager::Finalize();
	//}
	
	
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

	SafeDelete(earnscore);
}

void PlayScene::Activate()
{
	state = START;
	frame = 0;

	font = CreateFontToHandle("Oranienbaum", 80, 1);
	smallFont = CreateFontToHandle("Oranienbaum", 40, 1);
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

	//for (auto ptr : meteorite)
	//{
	//	Meteorite* me = new Meteorite;

	//	//隕石活性化
	//	me->Activate();
	//	MeteoriteManager::Entry(me);

	//	
	//}
	
	background->Activate();

	field->Activate();

	evaluation->Activate();

	//プレイヤー活性化
	player->Activate();
}

void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}

	++frame;
}

void PlayScene::UpdateStart(float deltaTime)
{
	/*if (frame > 120)
	{*/
		frame = 0;
		score = 0;
		state = GAME;
		
		earnscore->Activate();
		Score::GetInstance().Activate();
		

		TimeSlow::GetInstance().SetTimeSlow(slow);
		
		pUpdate = &PlayScene::UpdateGame;

		for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
		{
			if (meteorite[i] != nullptr)
			{
				//隕石活性化
				meteorite[i]->Activate();
			}
		}
		
		//ゲーム起動時の時間を取得
		startTime = GetNowCount();
	/*}*/
	
}

void PlayScene::UpdateGame(float deltaTime)
{
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

				//MeteoriteManager::PlayerAndMeteorite(player, ptr, explosion, evaluation, earnscore);

				//プレイヤーと隕石の当たり判定
				hitChecker->PlayerAndMeteorite(player, meteorite, explosion, evaluation, earnscore);
			}
		}
	}

	/*feverGauge = Score::GetInstance().GetScore() / static_cast<float>(50);
	if (feverGauge > 70.0f)
	{
		feverGauge = 0.0f;
		pUpdate = &PlayScene::UpdateFever;
	}*/
	
	//earnscoreのスコアを取得
	targetScore = Score::GetInstance().GetScore();

	//スコアを目標スコアに足し引き
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

	//TIMEが0になったら
	if (countDown == 0)
	{
		parent->SetNextScene(SceneManager::RESULT);
		return;
	}
}

void PlayScene::UpdateFever(float deltaTime)
{
	UpdateGame(deltaTime);

}

void PlayScene::DisplayScore()
{
	/*if (earnscore->aa())
	{*/
		int a = 100;
		
		DrawFormatStringToHandle(1000, a, GetColor(255, 255, 0), font, "SCORE : %d", score);
	/*}*/
}

void PlayScene::DisplayTime()
{
	
	DrawFormatStringToHandle(500, 100, GetColor(255, 0, 0), font, "TIME : %d", countDown);
	if (countDown < 10)
	{
		
	}
}

void PlayScene::Draw()
{
	//背景描画
	background->Draw();

	//プレイヤー描画
	player->Draw();

	//フィールド描画
	field->Draw();

	//爆発エフェクト描画
	explosion->Draw();

	//評価UIの描画
	evaluation->Draw();

	//UI管理クラスの描画
	uiManager->Draw(state, frame);

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//隕石描画
			meteorite[i]->Draw();
		}
	}

	//for (auto ptr : meteorite)
	//{
	//	//隕石マネージャー描画
	//	MeteoriteManager::Draw();
	//}

	//制限時間表示
	DisplayTime();

	//獲得スコア表示
	DisplayScore();
}