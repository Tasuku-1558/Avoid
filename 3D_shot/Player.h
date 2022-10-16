#pragma once

#include "DxLib.h"
#include "math3D.h"
#include "Collision.h"
#include "PlayerBase.h"


//PlayerBase�N���X���p��
class Player final : public PlayerBase
{
public:
	Player();    //�R���X�g���N�^
	~Player();   //�f�X�g���N�^

	void Initialize();
	void Update(float deltaTime);
	void Move(float deltaTime);
	void Draw() override;

	Math3d::Sphere GetCollsionSphere() { return CollisionSphere; }
	
private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^
	class HitChecker* hitchecker;
	
	Math3d::Sphere CollisionSphere;	//�����蔻�苅 
};