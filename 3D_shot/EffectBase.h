#pragma once


class EffectBase
{
public:
	 EffectBase(){/*�����Ȃ�*/};
	 virtual ~EffectBase(){/*�����Ȃ�*/ };

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Activate() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

private:
	EffectBase(const EffectBase&);		//�R�s�[�R���X�g���N�^
};