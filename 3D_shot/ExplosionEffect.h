#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

/// <summary>
/// 爆発エフェクトクラス
/// </summary>
class ExplosionEffect final : public EffectBase
{
public:
	ExplosionEffect(string effectPath, float effectSize);
	virtual ~ExplosionEffect();

	void Update(VECTOR position)override;		//更新処理
	void Draw()override;						//描画処理

private:
	ExplosionEffect(const ExplosionEffect&);	//コピーコンストラクタ
};