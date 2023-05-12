#pragma once

#include "PlayerBase.h"
#include "Math3D.h"

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player final : public PlayerBase
{
public:
	Player();
	virtual ~Player();

	void Update(float deltaTime);		//�X�V����
	void Draw();						//�`�揈��

	//�v���C���[�̏��
	enum class PlayerState
	{
		NOMAL,		//�ʏ���
		DAMAGE,		//��e���
	};

	struct Key
	{
		int input;			//�L�[����
		float position;		//�v���C���[�̈ʒu
		int range;			//�͈�
		VECTOR dir;			//����
	};

	PlayerState playerState;	//�v���C���[�̏��

private:
	Player(const Player&);		//�R�s�[�R���X�g���N�^

	void Initialize();						//����������
	void PlayerMove(float deltaTime);		//�v���C���[�ړ�����
	void LingMove(float deltaTime);			//�����O�ړ�����
	void KeyInput();						//�L�[���͏���
	void HitMeteorite(float deltaTime);		//覐΂ɏՓ˂���
	void AfterImage();						//�v���C���[�̎c������
	void Finalize();						//�I������
};