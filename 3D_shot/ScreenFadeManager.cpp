#include "ScreenFadeManager.h"
#include "Common.h"


const int ScreenFadeManager::FRAME_AMOUNT = 10;	//フレーム数

//コンストラクタ
ScreenFadeManager::ScreenFadeManager()
	: remainingDrawFrame(0)
	, alphaParameter(0)
	, pUpdate(nullptr)
	, pDraw(nullptr)
{
	//処理なし
}

//デストラクタ
ScreenFadeManager::~ScreenFadeManager()
{
	// 使用しない
}

ScreenFadeManager& ScreenFadeManager::GetInstance()
{
	static ScreenFadeManager screenFadeManager;
	return screenFadeManager;
}

//更新処理
void ScreenFadeManager::Update()
{
	//処理がなければ処理しない
	if (pUpdate == nullptr)
	{
		return;
	}

	(this->*pUpdate)();

	--remainingDrawFrame;	//フレーム数減少
}

//描画処理
void ScreenFadeManager::Draw()
{
	//処理がなければ処理しない
	if (pDraw == nullptr)
	{
		return;
	}

	(this->*pDraw)();
}

void ScreenFadeManager::FadeIn()
{
	//処理中であれば処理しない
	if (pUpdate != nullptr)
	{
		return;
	}

	remainingDrawFrame = FRAME_AMOUNT;

	//関数ポインタにフェードインをセット
	pUpdate = &ScreenFadeManager::UpdateFadeIn;
	pDraw   = &ScreenFadeManager::DrawFadeIn;
}

void ScreenFadeManager::FadeOut()
{
	//処理中であれば処理しない
	if (pUpdate != nullptr)
	{
		return;
	}

	remainingDrawFrame = FRAME_AMOUNT;

	//関数ポインタにフェードインをセット
	pUpdate = &ScreenFadeManager::UpdateFadeOut;
	pDraw   = &ScreenFadeManager::DrawFadeOut;
}

void ScreenFadeManager::Reset()
{
	// 処理中でないなら処理しない
	if (pUpdate == nullptr)
	{
		return;
	}

	remainingDrawFrame = 0;
	pUpdate = nullptr;
	pDraw = nullptr;
}

void ScreenFadeManager::UpdateFadeIn()
{
	// 残りフレーム数がなければ処理完了
	if (remainingDrawFrame <= 0)
	{
		pUpdate = nullptr;
		pDraw = nullptr;
		return;
	}

	float percentage = static_cast<float>(remainingDrawFrame) / static_cast<float>(FRAME_AMOUNT);	// 残りフレーム数
	alphaParameter = static_cast<int>(percentage * 255.0f);											// 0から255の値に変換
}

void ScreenFadeManager::UpdateFadeOut()
{
	// 残りフレーム数がなければ処理完了
	if (remainingDrawFrame <= 0)
	{
		pUpdate = nullptr;
		return;
	}

	float percentage = static_cast<float>(remainingDrawFrame) / static_cast<float>(FRAME_AMOUNT);	// 残りフレーム数
	alphaParameter = static_cast<int>(percentage * 255.0f);											// 0から255の値に変換
	alphaParameter = 255 - alphaParameter;															// アルファ値を変換
}

void ScreenFadeManager::DrawFadeIn()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaParameter); // ブレンドモード変更
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xff000000, TRUE);   // 黒四角形の描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // ブレンドモードを元に戻す
}

void ScreenFadeManager::DrawFadeOut()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaParameter); // ブレンドモード変更
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xff000000, TRUE);   // 黒四角形の描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // ブレンドモードを元に戻す
}

bool ScreenFadeManager::IsFinish()
{
	if (pUpdate == nullptr)
	{
		return true;
	}

	return false;
}
