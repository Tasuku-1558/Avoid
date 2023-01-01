#pragma once

class Meteorite;

/// <summary>
/// エフェクトのベースクラス
/// </summary>
class EffectBase
{
public:
	 EffectBase(){/*処理なし*/};
	virtual ~EffectBase(){/*処理なし*/};

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Activate() = 0;
	virtual void Update(Meteorite* meteorite) = 0;
	virtual void Draw() = 0;

private:
	EffectBase(const EffectBase&);		//コピーコンストラクタ
};