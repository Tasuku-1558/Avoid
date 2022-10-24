#pragma once

#include "Dxlib.h"
#include "Math3D.h"
#include "Collision.h"
#include "MeteoriteBase.h"

class Player;


//MeteoriteBase�N���X���p��
class Meteorite final : public MeteoriteBase
{
public:
	 Meteorite();
	~Meteorite();

	void Initialize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void Move(float deltaTime, Player* player);
	void Draw();
	
	
	Math3d::Sphere GetCollisionSphere() { return collisionSphere; } //�����蔻�苅��Ԃ�

private:
	Meteorite(const Meteorite&);				//�R�s�[�R���X�g���N�^

	Math3d::Sphere collisionSphere;				//�����蔻�苅

	int random;									//覐΂̃����_���l
	
	//�ÓI�萔
	static const int RANGE;						//�����_���l�͈̔�

};