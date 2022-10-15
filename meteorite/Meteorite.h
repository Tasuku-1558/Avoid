#pragma once

#include "Dxlib.h"
#include "math3D.h"
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
	void Update(float deltaTime, Player* player);
	void Move(float deltaTime, Player* player);
	void Draw() override;
	//void MeteoritePopCount(float deltaTime);
	//float GetMeteoriteCount() { return PopCount; }

	Math3d::Sphere GetCollisionSphere() { return CollisionSphere; } //�����蔻�苅��Ԃ�

	

private:
	Meteorite(const Meteorite&);				//�R�s�[�R���X�g���N�^
	

	Math3d::Sphere CollisionSphere;				//�����蔻�苅

};