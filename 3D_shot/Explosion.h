#pragma once

#include "EffectBase.h"

class Meteorite;

//Effect�̏��
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

	void Initialize() override;					//������
	void Finalize()override;
	void Activate()override;

	void Update(Meteorite* meteorite);			//�X�V
	void Estate(Meteorite* meteorite);
	void Draw() override;						//�`��

	enum class Effect effect;
private:
	int bi;
	int ai;
	/*int grBackgroundHandle;
	int grFrontHandle;*/

	
	int effectTime;
	float effectPos_X;
	float effectPos_Y;

	int playingEffectHandle;		// �Đ����̃G�t�F�N�g�̃n���h����������
};