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
	void Move(float deltaTime, Player* player);
	void Draw();
	
	Sphere GetCollisionSphere() { return collisionSphere; } //�����蔻�苅��Ԃ�

private:
	Meteorite(const Meteorite&);				//�R�s�[�R���X�g���N�^

	Sphere collisionSphere;				//�����蔻�苅

};