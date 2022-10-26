#include "LargeExplosion.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Meteorite.h"


LargeExplosion::LargeExplosion()
	: effectHandle(0)
	, effectPos_X(0.0f)
	, effectPos_Y(0.0f)
{
	//処理なし
}

LargeExplosion::~LargeExplosion()
{
	//処理なし
}

void LargeExplosion::Initialize()
{
	effectHandle = LoadEffekseerEffect("data/effect/LargeExplosion.efkefc", 30.0f);
	//grBackgroundHandle = LoadGraph(("data/texture/Background.png"));
	//grFrontHandle = LoadGraph(("data/texture/Front.png"));
}

void LargeExplosion::Finalize()
{
	// エフェクトリソースを削除
	DeleteEffekseerEffect(effectHandle);
}

void LargeExplosion::Activate()
{
}

void LargeExplosion::Update(Meteorite* meteorite)
{
	effectPos_X = meteorite->GetPosition().x;
	effectPos_Y = meteorite->GetPosition().y;

	// 定期的にエフェクトを再生
	if (time % 1 == 0)
	{
		// エフェクトを再生
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
	}

	// 再生中のエフェクトを移動
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos_X, effectPos_Y, 0);

	// 時間を経過
	time++;
}

void LargeExplosion::Draw()
{
	//DrawGraph(0, 0, grBackgroundHandle, TRUE);

	//// エフェクトの上にも画像を描画できる。
	//DrawGraph(0, 0, grFrontHandle, TRUE);

	// 再生中のエフェクトを更新
	UpdateEffekseer3D();

	// 再生中のエフェクトを描画
	DrawEffekseer3D();
}