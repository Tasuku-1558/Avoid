#pragma once

#include "Dxlib.h"
#include "MeteoriteBase.h"
#include "Math3D.h"

class Player;

using namespace Math3d;


/// <summary>
/// 覐΃N���X
/// MeteoriteBase�N���X���p��
/// </summary>
class Meteorite final : public MeteoriteBase
{
public:
	 Meteorite();
	~Meteorite();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void SpeedUp();					//覐΃X�s�[�h�A�b�v
	void RedColor();				//�eWave�ł�覐΂̐F�ύX
	void YellowColor();
	void OrangeCollor();
	void Draw();

private:
	Meteorite(const Meteorite&);				//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Player* player);		//�ړ�����

};