#pragma once

#include "Dxlib.h"
#include "MeteoriteBase.h"
#include "Math3D.h"

class Player;

/// <summary>
/// 覐΃N���X
/// MeteoriteBase�N���X���p��
/// </summary>
class Meteorite final : public MeteoriteBase
{
public:
	Meteorite();
	virtual ~Meteorite();

	void Initialize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void SpeedUp();														//覐΂̃X�s�[�h�ω�
	void ChangeColor(float red, float green, float blue);				//�eWave�ł�覐΂̐F�ύX
	void Draw();

private:
	Meteorite(const Meteorite&);					//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Player* player);		//�ړ�����
	void Finalize();

};