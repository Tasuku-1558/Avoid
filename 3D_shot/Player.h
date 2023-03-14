#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"

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
	void Activate();
	void Update(float deltaTime);
	void Draw();

	//�v���C���[�̏��
	enum class State
	{
		NOMAL,		//�ʏ���
		DAMAGE,		//��e���
	};

	State state;	//�v���C���[�̏��

private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^

	void Move(float deltaTime);					//�ړ�����
	void pUpdate(float deltaTime);				//�v���C���[�̏��
	void OnHitMeteorite(float deltaTime);		//覐΂ɓ��������Ȃ��
	void AfterImage();							//�v���C���[�̎c������
	void Finalize();							//�I������


	int emptyModel[3];			//�c�����f���i�[�p
	VECTOR pastPosition[3];		//�v���C���[�̉ߋ��̈ʒu
};