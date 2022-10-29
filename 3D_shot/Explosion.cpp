#include "Explosion.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Meteorite.h"


Explosion::Explosion()
	: /*effectHandle(0)*/
	  effectPos_X(0.0f)
	, effectPos_Y(0.0f)
	, effectTime(0)
	, playingEffectHandle(-1)
{
	effect = Effect::Nomal;
}

Explosion::~Explosion()
{
	//処理なし
}

void Explosion::Initialize()
{
	bi = LoadEffekseerEffect("data/effect/Explosion.efkefc", 30.0f);
	ai = LoadEffekseerEffect("data/effect/Explosion.efkefc", 10.0f);
	/*grBackgroundHandle = LoadGraph(("data/texture/Background.png"));
	grFrontHandle = LoadGraph(("data/texture/Front.png"));*/
}

void Explosion::Finalize()
{
	// エフェクトリソースを削除
	DeleteEffekseerEffect(bi);
}

void Explosion::Activate()
{
}

void Explosion::Update(Meteorite* meteorite)
{
	effectPos_X = meteorite->GetPosition().x;
	effectPos_Y = meteorite->GetPosition().y;

	// 定期的にエフェクトを再生
	if (effectTime % 1 == 0)
	{
		// エフェクトを再生
		playingEffectHandle = PlayEffekseer3DEffect(bi);
	}

	// 再生中のエフェクトを移動
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos_X, effectPos_Y, 0);

	// 時間を経過
	effectTime++;
}

void Explosion::Estate(Meteorite* meteorite)
{
	effectPos_X = meteorite->GetPosition().x;
	effectPos_Y = meteorite->GetPosition().y;

	// 定期的にエフェクトを再生
	if (effectTime % 1 == 0)
	{
		// エフェクトを再生
		playingEffectHandle = PlayEffekseer3DEffect(ai);
	}

	// 再生中のエフェクトを移動
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos_X, effectPos_Y, 0);

	// 時間を経過
	effectTime++;
}

void Explosion::Draw()
{
	//DrawGraph(0, 100, grBackgroundHandle, TRUE);

	//// エフェクトの上にも画像を描画できる。
	//DrawGraph(0, 100, grFrontHandle, TRUE);

	// 再生中のエフェクトを更新
	UpdateEffekseer3D();

	// 再生中のエフェクトを描画
	DrawEffekseer3D();
}