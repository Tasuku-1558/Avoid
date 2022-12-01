#include "Explosion.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Meteorite.h"


Explosion::Explosion()
	: effectHandle(0)
	, effectPos_X(0.0f)
	, effectPos_Y(0.0f)
	, effectPos_Z(0.0f)
	, effectTime(0)
	, playingEffectHandle(0)
	, explosionSE(0)
{
	//処理なし
}

Explosion::~Explosion()
{
	//処理なし
}

void Explosion::Initialize()
{
	effectHandle = LoadEffekseerEffect("data/effect/Explosion.efkefc", 15.0f);
	explosionSE = LoadSoundMem("data/sound/ExplosionSE.mp3");
}

void Explosion::Finalize()
{
	// エフェクトリソースを削除
	DeleteEffekseerEffect(effectHandle);

	// サウンドリソースを削除
	InitSoundMem();
}

void Explosion::Activate()
{
	// エフェクトを停止する
	StopEffekseer3DEffect(playingEffectHandle);
}

void Explosion::Update(Meteorite* meteorite)
{
	effectPos_X = meteorite->GetPosition().x;
	effectPos_Y = meteorite->GetPosition().y;
	effectPos_Z = meteorite->GetPosition().z;

	// 定期的にエフェクトを再生
	if (effectTime % 1 == 0)
	{
		// エフェクトを再生
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// 爆発SEを再生
		PlaySoundMem(explosionSE, DX_PLAYTYPE_BACK);
	}

	// 再生中のエフェクトを移動
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos_X, effectPos_Y, effectPos_Z);

	// 時間を経過
	effectTime++;
}

void Explosion::Draw()
{
	// 再生中のエフェクトを更新
	UpdateEffekseer3D();

	// 再生中のエフェクトを描画
	DrawEffekseer3D();
}