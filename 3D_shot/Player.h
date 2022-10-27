#pragma once

#include "DxLib.h"
#include "Math3D.h"
#include "Collision.h"
#include "PlayerBase.h"

//Player�̏��
enum class State
{
	Nomal,
	Miss,
};

//PlayerBase�N���X���p��
class Player final : public PlayerBase
{
public:
	 Player();    //�R���X�g���N�^
	~Player();    //�f�X�g���N�^

	void Initialize();
	void Activate();
	void Update(float deltaTime);
	void Pstate(float deltaTime);
	void Move(float deltaTime);
	void Damege(float deltaTime);
	void Draw() override;

	Math3d::Sphere GetCollsionSphere() { return collisionSphere; }
	enum class State state;
private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^

	bool noDrawFrame;				//�`�悵�Ȃ��t���[����
	int damegeCount;

	Math3d::Sphere collisionSphere;	//�����蔻�苅 
};