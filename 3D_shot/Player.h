#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"


using namespace Math3d;

/// <summary>
/// �v���C���[�̏��
/// </summary>
enum class State
{
	NOMAL,
	DAMAGE,
};


/// <summary>
/// �v���C���[�N���X
/// PlayerBase�N���X���p��
/// </summary>
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
	void pUpdate();					//�v���C���[�̏��
	void OnHitMeteorite();			//覐΂ɓ��������Ȃ��

};