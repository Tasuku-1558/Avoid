#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

/// <summary>
/// �����G�t�F�N�g�N���X
/// </summary>
class Explosion final : public EffectBase
{
public:
	Explosion(string effectPath, float effectSize);
	virtual ~Explosion();

	void Update(VECTOR position)override;		//�X�V����
	void Draw()override;						//�`�揈��

private:
	Explosion(const Explosion&);				//�R�s�[�R���X�g���N�^
};