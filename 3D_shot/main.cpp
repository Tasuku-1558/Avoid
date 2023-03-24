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
	
	//シャドウマップハンドルの作成
	int shadowMapHandle = MakeShadowMap(SHADOWMAP_SIZE_X, SHADOWMAP_SIZE_Y);

	//シャドウマップが想定するライトの方向をセット
	SetShadowMapLightDirection(shadowMapHandle, LIGHT_DIRECTION);

	//シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(shadowMapHandle, SHADOWMAP_MINPOSITION, SHADOUMAP_MAXPOSITION);

	//フォント変更
	LPCSTR fontPath = "Data/Font/Oranienbaum.ttf";

	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {}
	else { MessageBox(NULL, "フォント読込失敗", "", MB_OK); }

	//時間計測
	LONGLONG nowTime;
	LONGLONG prevTime = nowTime = GetNowHiPerformanceCount();

	//待機フレーム時間(60fps)
	float waitFrameTime = 16667.0f;

	//メインループ用フラグ変数
	bool loop = true;
	
	//モデル管理クラスの生成
	ModelManager::GetInstance();

	//サウンド管理クラスの生成
	SoundManager::GetInstance();

	//今のシーン
	SceneType nowSceneType;

	//ひとつ前のシーン
	SceneType prevSceneType = nowSceneType = SceneType::TITLE;

	//シーンを生成
	SceneBase* sceneBase = new TitleScene();

	//メインループ
	while (loop)
	{
		//前フレームと現在のフレームの差分
		float deltaTime;

		//現在のフレームを更新
		nowTime = GetNowHiPerformanceCount();
		
		//true：動きを遅くする false：通常状態
		bool slow = TimeSlow::GetInstance().GetTimeSlow();

		if (slow)
		{
			deltaTime = (nowTime - prevTime) / 3000000.0f;
		}
		else
		{
			deltaTime = (nowTime - prevTime) / 1000000.0f;
		}

		//DxlibのカメラとEffekseerのカメラを同期
		Effekseer_Sync3DSetting();

		SoundManager::GetInstance().SeUpdate();

		nowSceneType = sceneBase->Update(deltaTime);		//各シーンの更新処理

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
		
		//デバック用　デルタタイム計測
		DrawFormatString(0, 500, GetColor(255, 255, 255), "%f", deltaTime, TRUE);

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
			delete sceneBase;									//シーンの解放
			sceneBase = sceneBase->CreateScene(nowSceneType);	//シーンの生成
		}

		//直前のシーンを記録
		prevSceneType = nowSceneType;

		//60fps制御用ループ
		while (GetNowHiPerformanceCount() - nowTime < waitFrameTime);

		prevTime = nowTime;
	}

	//フォントのアンロード
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {}
	else { MessageBox(NULL, "remove failure", "", MB_OK); }

	DeleteShadowMap(shadowMapHandle);	//シャドウマップの削除

	delete sceneBase;			//シーンの解放
	
	Effkseer_End();				//Effekseerの終了処理
	
	DxLib_End();				//Dxlib使用の終了処理

	return 0;					//ソフトの終了 
}