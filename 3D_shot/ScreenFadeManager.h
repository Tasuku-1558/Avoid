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
	void Reset();

private:

	 ScreenFadeManager();								//コンストラクタ
	 ScreenFadeManager(const ScreenFadeManager&);		//コピーコンストラクタ
	~ScreenFadeManager();								//デストラクタ

	//静的定数
	static const int FRAME_NUMBER;
};