#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"


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

	enum class State state;

private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^

	void Move(float deltaTime);		//�ړ�����
	void pUpdate();					//��ԕω�
	void OnHitMeteorite();			//覐΂ɓ�������

};