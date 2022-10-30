#pragma once

#include "EffectBase.h"

class Meteorite;

//�����G�t�F�N�g�N���X
class Explosion final : public EffectBase
{
public:
	 Explosion();
	~Explosion()override;

	void Initialize()override;					//������
	void Finalize()override;
	void Activate()override;

	void Update(Meteorite* meteorite);			//�X�V
	void Draw() override;						//�`��

private:
	
	int effectHandle;
	int explosionSE;
	int effectTime;

	float effectPos_X;
	float effectPos_Y;
	float effectPos_Z;

	int playingEffectHandle;		// �Đ����̃G�t�F�N�g�̃n���h����������
};