//-----------------------------------------------------------------------------
// メイン処理
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Common.h"
#include "SceneManager.h"
#include "ModelManager.h"

#pragma warning(disable:4996)

using std::string;

//-----------------------------------------------------------------------------
// メイン関数
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);			// ログファイルを出力しない
	ChangeWindowMode(IS_WINDOW_MODE);				// ウィンドウモードにするか
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);	// 画面モードのセット
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// DXライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// Effekseerを初期化処理
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}
	
	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Zバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	// 時間計測
	int nowTime;
	int prevTime = nowTime = GetNowCount();
	
	ModelManager::GetInstance();	//モデル管理クラスの生成

	SceneManager* sceneManager = new SceneManager();

	sceneManager->Initialize();

	// エスケープキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// フレーム時間を算出
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime) / 1000.0f;

		// DXライブラリのカメラとEffekseerのカメラを同期
		Effekseer_Sync3DSetting();
		
		sceneManager->Update(deltaTime);

		// 画面を初期化する
		ClearDrawScreen();

		sceneManager->Draw();
		
		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		//次のシーンがENDなら
		if (sceneManager->GetNextScene() == SceneManager::END)
		{
			break;
		}
		
		prevTime = nowTime;
	}

	SafeDelete(sceneManager);	// シーンマネージャーの解放

	Effkseer_End();				// Effekseerの終了処理
	
	DxLib_End();				// DXライブラリ使用の終了処理

	return 0;					// ソフトの終了 
}