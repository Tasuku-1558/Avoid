#include "Explosion.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"


const string Explosion::EFFECT_FOLDER_PATH = "data/effect/";		//effectフォルダまでのパス
const string Explosion::EXPLOSION_PATH	   = "Explosion.efkefc";	//爆発エフェクトのパス
const string Explosion::SOUND_FOLDER_PATH  = "data/sound/";			//soundフォルダまでのパス
const string Explosion::EXPLOSION_SE_PATH  = "ExplosionSE.mp3";		//爆発SEのパス


/// <summary>
/// コンストラクタ
/// </summary>
Explosion::Explosion()
	: effectHandle(0)
	, effectTime(0)
	, playingEffectHandle(0)
	, explosionSE(0)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Explosion::~Explosion()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Explosion::Initialize()
{
	string failePath = EFFECT_FOLDER_PATH + EXPLOSION_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), 15.0f);

	failePath = SOUND_FOLDER_PATH + EXPLOSION_SE_PATH;
	explosionSE = LoadSoundMem(failePath.c_str());
}

/// <summary>
/// 終了処理
/// </summary>
void Explosion::Finalize()
{
	// エフェクトリソースを削除
	DeleteEffekseerEffect(effectHandle);

	// サウンドリソースを削除
	InitSoundMem();
}

/// <summary>
/// 活性化処理
/// </summary>
void Explosion::Activate()
{
	// エフェクトを停止する
	StopEffekseer3DEffect(playingEffectHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="effectPos"></param>
void Explosion::Update(VECTOR effectPos)
{
	// 定期的にエフェクトを再生
	if (effectTime % 1 == 0)
	{
		// エフェクトを再生
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// 爆発SEを再生
		PlaySoundMem(explosionSE, DX_PLAYTYPE_BACK);
	}

	// 再生中のエフェクトを移動
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos.x, effectPos.y, effectPos.z);

	// 時間を経過
	effectTime++;
}

/// <summary>
/// 描画処理
/// </summary>
void Explosion::Draw()
{
	// 再生中のエフェクトを更新
	UpdateEffekseer3D();

	// 再生中のエフェクトを描画
	DrawEffekseer3D();
}