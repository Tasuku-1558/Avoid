#pragma once

#include "EffectBase.h"

class Meteorite;

//爆発エフェクトクラス
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
	
	int effectHandle;
	int explosionSE;
	int effectTime;

	float effectPos_X;
	float effectPos_Y;
	float effectPos_Z;

	int playingEffectHandle;		// 再生中のエフェクトのハンドルを初期化
};