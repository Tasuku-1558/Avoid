#pragma once

#include "DxLib.h"
#include "Math3D.h"
#include "Collision.h"
#include "PlayerBase.h"


//PlayerBase�N���X���p��
class Player final : public PlayerBase
{
public:
	 Player();    //�R���X�g���N�^
	~Player();    //�f�X�g���N�^

	void Initialize();
	void Activate();
	void Update(float deltaTime);
	void Move(float deltaTime);
	void Draw() override;

	Math3d::Sphere GetCollsionSphere() { return collisionSphere; }

private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^

	Math3d::Sphere collisionSphere;	//�����蔻�苅 
};