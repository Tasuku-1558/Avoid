#pragma once

#include "DxLib.h"

//画面効果クラス
//シングルトン
class ScreenFadeManager final
{
public:
	static ScreenFadeManager& GetInstance();		//アドレスを返す

	void Update();
	void Draw();

	void FadeIn();
	void FadeOut();
	void Reset();		//処理中なら処理を終了
	bool IsFinish();	//処理が終わっているかどうか

private:

	 ScreenFadeManager();								//コンストラクタ
	 ScreenFadeManager(const ScreenFadeManager&);		//コピーコンストラクタ
	~ScreenFadeManager();								//デストラクタ

	void(ScreenFadeManager::* pUpdate)();	//Update関数ポインタ
	void(ScreenFadeManager::* pDraw)();		//Draw関数ポインタ

	void UpdateFadeIn();
	void DrawFadeIn();
	void UpdateFadeOut();
	void DrawFadeOut();

	int remainingDrawFrame;  // 残りの描画するframe数
	int alphaParameter; // ALPHA値(0～255)

	//静的定数
	static const int FRAME_AMOUNT;		//フレーム数
};