#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

/// <summary>
/// �����G�t�F�N�g�N���X
/// </summary>
class ExplosionEffect final : public EffectBase
{
public:
	ExplosionEffect(string effectPath, float effectSize);
	virtual ~ExplosionEffect();

	void Update(VECTOR position)override;		//�X�V����
	void Draw()override;						//�`�揈��

private:
	ExplosionEffect(const ExplosionEffect&);	//�R�s�[�R���X�g���N�^
};