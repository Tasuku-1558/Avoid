#include "PlayScene.h"
#include "DxLib.h"
#include "Player.h"
#include "Meteorite.h"
#include "Camera.h"
#include "HitChecker.h"
#include "Utility.h"

const int PlayScene::GameTime = 60;

PlayScene::PlayScene():SceneBase(SceneType::PLAY)
		, camera(new Camera())
		, player(new Player())
		, MeteoritePopFlag(false)
		, StartTime(0)
		, NowTime(0)
		, CountDown(0)
		, GameBackground(0)
		, Score(0)
{
	//隕石の生成
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		meteorite[i] = new Meteorite();
	}

	//プレイヤー初期化
	player->Initialize();

	//隕石初期化
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			meteorite[i]->Initialize();
		}
	}

	//ゲーム起動時の時間を取得
	StartTime = GetNowCount();
}

PlayScene::~PlayScene()
{
	//カメラを解放
	SAFE_DELETE(camera);

	//プレイヤーを解放
	SAFE_DELETE(player);

	//隕石を解放
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			SAFE_DELETE(meteorite[i]);
		}
	}

	//ゲーム背景を解放
	DeleteGraph(GameBackground);
}

void PlayScene::Initialize()
{
	////隕石クラスのポインタを確保するための配列作成
	//Meteorite* meteorite[Meteorite::METEORITE_ARRAY_NUMBER] = { nullptr };

	//ゲーム背景
	GameBackground = LoadGraph("data/Image/galaxy.png");


}


SceneType PlayScene::Update(float deltaTime)
{
	//カメラの制御
	camera->Update();

	//プレイヤーの制御
	player->Update(deltaTime);

	MeteoritePopFlag = true;

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//隕石出現フラグがtrueの時
			if (MeteoritePopFlag)
			{
				//隕石出現カウント
				//meteorite[i]->MeteoritePopCount(deltaTime);
				MeteoritePopFlag = false;

				//隕石制御
				meteorite[i]->Update(deltaTime, player);

				//プレイヤーと隕石の当たり判定
				HitChecker::PlayerAndMeteorite(player, meteorite);
			}
			
			////隕石出現カウント
			//if (meteorite[i]->GetMeteoriteCount() > 0.01f)
			//{
			//	
			//}
		}
	}



	//デバック用
	x = player->GetPosition().x;
	y = player->GetPosition().y;
	Direction = HitChecker::GetDirection();

	//ヒットチェッカーのスコアを取得
	TargetScore = HitChecker::GetScore();

	//スコアを目標スコアに足していく処理
	if (TargetScore != Score)
	{
		if (TargetScore > Score)
		{
			Score += 100;
		}
		else
		{
			Score -= 100;
		}
	}
	
	NowTime = GetNowCount();
	CountDown = GameTime - (NowTime - StartTime) / 1000;

	//制限時間が0になったら
	if (CountDown == 0)
	{
		NowSceneType = SceneType::RESULT;
	}

	return NowSceneType;
}

void PlayScene::Draw()
{
	//ゲーム背景描画
	DrawBillboard3D(VGet(0.0f, 300.0f, 1200.0f), 0.5f, 0.5f, 4000.0f, 0.0f, GameBackground, TRUE);

	//プレイヤー描画
	player->Draw();

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//隕石描画
			meteorite[i]->Draw();
		}
	}

	
	SetFontSize(60);			//文字のフォントサイズ変更
	ChangeFont("ＭＳ 明朝");	//種類をMS明朝に変更

	//制限時間表示
	DrawFormatString(500, 100, GetColor(255, 0, 0), "TIME : %d", CountDown);

	//獲得スコア表示
	DrawFormatString(500, 150, GetColor(255, 255, 0), "Score : %d", Score);

	//デバック用
	DrawFormatString(500, 400, GetColor(255, 0, 0), "x : %d", x);
	DrawFormatString(500, 450, GetColor(255, 0, 0), "y : %d", y);
	DrawFormatString(500, 500, GetColor(255, 0, 0), "Direction : %f", Direction);
}