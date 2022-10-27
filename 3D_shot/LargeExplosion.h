#pragma once

#include "EffectBase.h"

class Meteorite;

class LargeExplosion final : public EffectBase
{
public:
	 LargeExplosion();
	~LargeExplosion()override;

	void Initialize() override;					//初期化
	void Finalize()override;
	void Activate()override;
	void Update(Meteorite* meteorite);			//更新
	void Draw() override;						//描画


private:
	int effectHandle;
	/*int grBackgroundHandle;
	int grFrontHandle;*/
	
	int effectTime;
	float effectPos_X;
	float effectPos_Y;

	int playingEffectHandle;		// 再生中のエフェクトのハンドルを初期化
};