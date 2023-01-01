#include "Explosion.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Meteorite.h"


const string Explosion::EFFECT_FOLDER_PATH = "data/effect/";		//effectフォルダまでのパス
const string Explosion::EXPLOSION_PATH	   = "Explosion.efkefc";	//爆発エフェクトのパス
const string Explosion::SOUND_FOLDER_PATH  = "data/sound/";			//soundフォルダまでのパス
const string Explosion::EXPLOSION_SE_PATH  = "ExplosionSE.mp3";		//爆発SEのパス

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
	string failePath = EFFECT_FOLDER_PATH + EXPLOSION_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), 15.0f);

	failePath = SOUND_FOLDER_PATH + EXPLOSION_SE_PATH;
	explosionSE = LoadSoundMem(failePath.c_str());
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