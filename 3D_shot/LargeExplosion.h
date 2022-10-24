#pragma once

#include "EffectBase.h"

class LargeExplosion final : public EffectBase
{
public:
	 LargeExplosion();
	~LargeExplosion()override;

	void Initialize() override;					//‰Šú‰»
	void Finalize()override;
	void Activate()override;
	void Update() override;						//XV
	void Draw() override;						//•`‰æ

private:

};