#pragma once

#include "EffectBase.h"

class Meteorite;

//Effectの状態
enum class Effect
{
	Nomal = 0,
	Excellent,
	Great,
	Good,
};

class Explosion final : public EffectBase
{
public:
	 Explosion();
	~Explosion()override;

	void Initialize() override;					//初期化
	void Finalize()override;
	void Activate()override;
	void Update(Meteorite* meteorite);			//更新
	void Estate();
	void Draw() override;						//描画


private:
	int effectHandle;
	/*int grBackgroundHandle;
	int grFrontHandle;*/

	enum class Effect effect;
	
	int effectTime;
	float effectPos_X;
	float effectPos_Y;

	int playingEffectHandle;		// 再生中のエフェクトのハンドルを初期化
};