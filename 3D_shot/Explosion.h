#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

class Meteorite;

/// <summary>
/// 爆発エフェクトクラス
/// </summary>
class Explosion final : public EffectBase
{
public:
	 Explosion();
	~Explosion()override;

	void Initialize()override;					//初期化
	void Finalize()override;
	void Activate()override;

	void Update(Meteorite* meteorite);			//更新
	void Draw() override;						//描画

private:
	
	int effectHandle;				//爆発エフェクト格納用
	int explosionSE;				//爆発SE格納用
	int effectTime;					//エフェクト時間

	//爆発エフェクトの位置
	float effectPos_X;
	float effectPos_Y;
	float effectPos_Z;

	int playingEffectHandle;		// 再生中のエフェクトのハンドルを初期化


	//静的定数
	static const string EFFECT_FOLDER_PATH;		//effectフォルダまでのパス
	static const string SOUND_FOLDER_PATH;		//soundフォルダまでのパス
	static const string EXPLOSION_PATH;			//爆発エフェクトのパス
	static const string EXPLOSION_SE_PATH;		//爆発SEのパス

};