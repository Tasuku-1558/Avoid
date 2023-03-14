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
	Explosion(string effectPath, float effectSize);
	virtual ~Explosion();

	void Update(VECTOR position)override;		//更新処理
	void Draw()override;						//描画処理

private:
	Explosion(const Explosion&);				//コピーコンストラクタ
};