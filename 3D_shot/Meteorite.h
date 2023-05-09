#pragma once

#include "MeteoriteBase.h"

/// <summary>
/// 覐΃N���X
/// </summary>
class Meteorite final : public MeteoriteBase
{
public:
	Meteorite(VECTOR inPlayerPosition);
	virtual ~Meteorite();

	void Update(float deltaTime);	//�X�V����
	void Draw();					//�`�揈��

	void SpeedUp();					//覐΂̃X�s�[�h�ω�

private:
	Meteorite(const Meteorite&);	//�R�s�[�R���X�g���N�^

	void Initialize();				//����������
	void Move(float deltaTime);		//�ړ�����
	void Finalize();				//�I������
};