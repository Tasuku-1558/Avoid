#pragma once

#include "EffectBase.h"

class Meteorite;

class LargeExplosion final : public EffectBase
{
public:
	 LargeExplosion();
	~LargeExplosion()override;

	void Initialize() override;					//������
	void Finalize()override;
	void Activate()override;
	void Update(Meteorite* meteorite);			//�X�V
	void Draw() override;						//�`��


private:
	int effectHandle;
	/*int grBackgroundHandle;
	int grFrontHandle;*/
	
	int effectTime;
	float effectPos_X;
	float effectPos_Y;

	int playingEffectHandle;		// �Đ����̃G�t�F�N�g�̃n���h����������
};