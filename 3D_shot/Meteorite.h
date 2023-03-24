#pragma once

#include "MeteoriteBase.h"
#include "Math3D.h"

class Player;

/// <summary>
/// 覐΃N���X
/// </summary>
class Meteorite final : public MeteoriteBase
{
public:
	Meteorite();
	virtual ~Meteorite();

	void Update(float deltaTime, Player* player);		//�X�V����
	void Draw();										//�`�揈��

	void SpeedUp();														//覐΂̃X�s�[�h�ω�
	void ChangeColor(float red, float green, float blue);				//�eWave�ł�覐΂̐F�ύX

private:
	Meteorite(const Meteorite&);					//�R�s�[�R���X�g���N�^

	void Initialize();								//����������
	void Activate();								//����������
	void Move(float deltaTime, Player* player);		//�ړ�����
	void Finalize();								//�I������

};