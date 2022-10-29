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
	void Estate();
	void Draw() override;						//�`��


private:
	int effectHandle;
	/*int grBackgroundHandle;
	int grFrontHandle;*/

	enum class Effect effect;
	
	int effectTime;
	float effectPos_X;
	float effectPos_Y;

	int playingEffectHandle;		// �Đ����̃G�t�F�N�g�̃n���h����������
};