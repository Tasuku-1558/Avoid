#include "ScreenFadeManager.h"


const int ScreenFadeManager::FRAME_AMOUNT = 120;	//フレーム数

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
}

void ScreenFadeManager::UpdateFadeIn()
{
}

void ScreenFadeManager::DrawFadeIn()
{
}

void ScreenFadeManager::UpdateFadeOut()
{
}

void ScreenFadeManager::DrawFadeOut()
{
}



bool ScreenFadeManager::IsFinish()
{
	return false;
}
