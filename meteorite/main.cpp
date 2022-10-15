//-----------------------------------------------------------------------------
// @brief  メイン処理
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "ModelManager.h"
#include "Common.h"
#include "Utility.h"

#pragma warning(disable:4996)

using std::string;


//新しいシーンを生成する
SceneBase* CreateScene(SceneType Now)
{
	SceneBase* RetScene = nullptr;

	switch (Now)
	{
	case SceneType::TITLE:
		RetScene = new TitleScene;
		break;

	case SceneType::PLAY:
		RetScene = new PlayScene;
		break;

	case SceneType::RESULT:
		RetScene = new ResultScene;
		break;

	default:
		break;
	}
	return RetScene;
}

//-----------------------------------------------------------------------------
// @brief  メイン関数
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);			// ログファイルを出力しない
	ChangeWindowMode(IS_WINDOW_MODE);				// ウィンドウモードにするか
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);	//画面モードのセット

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//ひとつ前のシーン
	SceneType PrevSceneType = SceneType::PLAY/*TITLE*/;

	//今のシーン
	SceneType NowSceneType = SceneType::PLAY/*TITLE*/;
	
	// 時間計測
	int nowTime = GetNowCount();
	int prevTime = nowTime;
	
	//シーンを生成
	SceneBase* scenebase = new PlayScene/*TitleScene*/;

	ModelManager::GetInstance();	//モデル管理クラスの生成
	
	// エスケープキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// フレーム時間を算出
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime) / 1000.0f;
		
		scenebase->Initialize();

		NowSceneType = scenebase->Update(deltaTime);
		

		//画面背景の色
		SetBackgroundColor(0, 0, 255);

		// 画面を初期化する
		ClearDrawScreen();

		scenebase->Draw();
		
		//位置関係がわかるように
		//後で消す
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

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		//SceneTypeが切り替わったらシーンの切り替え
		if (NowSceneType != PrevSceneType)
		{
			SAFE_DELETE(scenebase);						//シーンの解放
			scenebase = CreateScene(NowSceneType);		//シーンの生成
		}


		prevTime = nowTime;

		//直前のシーンを記録
		PrevSceneType = NowSceneType;
	}

	SAFE_DELETE(scenebase);	//シーンの解放
	
	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}