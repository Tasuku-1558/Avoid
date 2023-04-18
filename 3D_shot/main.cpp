#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "SoundManager.h"
#include "TimeSlow.h"

#include "TitleScene.h"


//メインプログラム
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(IS_WINDOW_MODE);						//ウィンドウモードにするか
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT);	//画面モードのセット
	SetUseDirect3DVersion(DX_DIRECT3D_11);					//DirectX11を使用するようにする
	SetOutApplicationLogValidFlag(FALSE);					//ログファイルを出力しない

	//Dxlib初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			//エラーが起きたら直ちに終了
	}

	//Effekseerを初期化処理
	//引数は画面に表示する最大パーティクル数を設定
	if (Effekseer_Init(MAX_PARTICLE_NUMBER) == -1)
	{
		DxLib_End();
		return -1;
	}

	//描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	//フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	//Dxlibがデバイスロストした時のコールバックを設定する
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//Zバッファを有効にする
	SetUseZBuffer3D(TRUE);

	//Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);
	
	//フォント変更
	LPCSTR fontPath = "Data/Font/Oranienbaum.ttf";

	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {}
	else { MessageBox(NULL, "フォント読込失敗", "", MB_OK); }

	//時間計測
	LONGLONG nowTime;
	LONGLONG prevTime = nowTime = GetNowHiPerformanceCount();

	//メインループ用フラグ変数
	bool loop = true;

	//シャドウマップハンドルの作成
	int shadowMapHandle = MakeShadowMap(SCREEN_WIDTH, SCREEN_HEIGHT);

	//シャドウマップが想定するライトの方向をセット
	SetShadowMapLightDirection(shadowMapHandle, LIGHT_DIRECTION);

	//シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(shadowMapHandle, SHADOWMAP_MINPOSITION, SHADOUMAP_MAXPOSITION);
	
	//モデル管理クラスの生成
	ModelManager::GetInstance();

	//サウンド管理クラスの生成
	SoundManager::GetInstance();

	//ひとつ前のシーン
	SceneType prevSceneType;

	//今のシーン
	SceneType nowSceneType = prevSceneType = SceneType::TITLE;

	//シーンを生成
	SceneBase* sceneBase = new TitleScene();

	//メインループ
	while (loop)
	{
		SceneBase* scene = nullptr;

		//前フレームと現在のフレームの差分
		float deltaTime;

		//現在のフレームを更新
		nowTime = GetNowHiPerformanceCount();
		
		bool slow = TimeSlow::GetInstance().GetTimeSlow();

		//フレームの動きを遅くする
		if (slow)
		{
			deltaTime = (nowTime - prevTime) / A;
		}
		else
		{
			deltaTime = (nowTime - prevTime) / B;
		}

		//マウスカーソルを表示しない
		SetMouseDispFlag(FALSE);

		//DxlibのカメラとEffekseerのカメラを同期
		Effekseer_Sync3DSetting();

		SoundManager::GetInstance().SeUpdate();

		nowSceneType = sceneBase->Update(deltaTime);	//各シーンの更新処理

		//画面を初期化する
		ClearDrawScreen();

		//シャドウマップへの描画の準備
		ShadowMap_DrawSetup(shadowMapHandle);

		sceneBase->Draw();     //各シーンの描画処理

		//シャドウマップへの描画を終了
		ShadowMap_DrawEnd();

		//描画に使用するシャドウマップを設定
		SetUseShadowMap(0, shadowMapHandle);

		sceneBase->Draw();     //各シーンの描画処理

		//描画に使用するシャドウマップの設定を解除
		SetUseShadowMap(0, -1);
		
		//裏画面の内容を表画面に反映させる
		ScreenFlip();

		//次のシーンがENDならメインループを抜ける
		if (nowSceneType == SceneType::END || CheckHitKey(KEY_INPUT_ESCAPE))
		{
			loop = false;
			break;
		}

		//今のシーンが前のシーンと違うなら
		if (nowSceneType != prevSceneType)
		{
			delete sceneBase;								//シーンの解放
			sceneBase = scene->CreateScene(nowSceneType);	//シーンの生成
		}

		//直前のシーンを記録
		prevSceneType = nowSceneType;

		//60fps制御用ループ
		while (GetNowHiPerformanceCount() - nowTime < WAIT_FRAME_TIME);

		prevTime = nowTime;
	}

	//フォントの削除
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {}
	else { MessageBox(NULL, "remove failure", "", MB_OK); }

	delete sceneBase;						//シーンの解放

	DeleteShadowMap(shadowMapHandle);		//シャドウマップの削除
	
	Effkseer_End();							//Effekseerの終了処理
	
	DxLib_End();							//Dxlib使用の終了処理

	return 0;								//ソフトの終了 
}