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

	PlayerState playerState;	//�v���C���[�̏��

private:
	Player(const Player&);		//�R�s�[�R���X�g���N�^

	void Initialize();							//����������
	void Activate();							//����������
	void Move(float deltaTime);					//�ړ�����
	void KeyInput();							//�L�[���͏���
	void HitMeteorite(float deltaTime);			//覐΂ɏՓ˂���
	void AfterImage();							//�v���C���[�̎c������
	void Finalize();							//�I������

};