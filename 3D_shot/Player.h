#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Collision.h"


using namespace Math3d;

enum class State
{
	Nomal,
	Damage,
};

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
	void Draw();

	Sphere GetCollsionSphere() { return collisionSphere; }

	enum class State state;

private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^

	void Move(float deltaTime);		//�ړ�����
	void pUpdate();					//��ԕω�
	void OnHitMeteorite();			//覐΂ɓ�������

	Sphere collisionSphere;			//�����蔻�苅 

	int lingModel;
	VECTOR rotate;
	VECTOR rotate_Speed;

	int damageCount;
	bool noDrawFrame;

	static const VECTOR LING_SIZE;				//�����O�{��
	static const VECTOR LING_ROTATE;			//�����O��]�p�x
	static const VECTOR LING_ROTATE_SPEED;		//�����O��]�X�s�[�h
	
};