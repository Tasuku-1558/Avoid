#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Collision.h"


using namespace Math3d;

//�v���C���[�N���X
//PlayerBase�N���X���p��
class Player final : public PlayerBase
{
public:
	 Player();    //�R���X�g���N�^
	~Player();    //�f�X�g���N�^

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Move(float deltaTime);
	void Draw();

	Sphere GetCollsionSphere() { return collisionSphere; }

private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^

	Sphere collisionSphere;			//�����蔻�苅 
};