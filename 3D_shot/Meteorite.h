#pragma once

#include "Dxlib.h"
#include "MeteoriteBase.h"
#include "Math3D.h"
#include "Collision.h"


class Player;

using namespace Math3d;

//覐΃N���X
//MeteoriteBase�N���X���p��
class Meteorite final : public MeteoriteBase
{
public:
	 Meteorite();
	~Meteorite();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void SpeedUp();
	void Draw();
	
	Sphere GetCollisionSphere() { return collisionSphere; } //�����蔻�苅��Ԃ�


private:
	Meteorite(const Meteorite&);				//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Player* player);					//�ړ�����
	
	int shadowMapHandle;
	int shadowImage;					//覐Ήe
	VECTOR shadowPosition;				//覐Ήe�ʒu
	Sphere collisionSphere;				//�����蔻�苅

};