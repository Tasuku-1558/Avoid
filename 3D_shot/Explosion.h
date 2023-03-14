#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

/// <summary>
/// 爆発エフェクトクラス
/// </summary>
class Explosion final : public EffectBase
{
public:
	Explosion();
	virtual ~Explosion();

	void Initialize()override;					//初期化処理
	void Finalize()override;					//終了処理
	void Activate()override;					//活性化処理
	void Update(VECTOR effectPos)override;		//更新処理
	void Draw()override;						//描画処理

private:
	
	int effectHandle;				//爆発エフェクト格納用
	int explosionSE;				//爆発SE格納用
	int effectTime;					//エフェクト時間
	int playingEffectHandle;		//再生中のエフェクトのハンドルを初期化


	//静的定数
	static const string EFFECT_FOLDER_PATH;		//effectフォルダまでのパス
	static const string SOUND_FOLDER_PATH;		//soundフォルダまでのパス
	static const string EXPLOSION_PATH;			//爆発エフェクトのパス
	static const string EXPLOSION_SE_PATH;		//爆発SEのパス

};