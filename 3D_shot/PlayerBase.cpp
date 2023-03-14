#include "PlayerBase.h"


const float  PlayerBase::SPEED		 = 400.0f;						//�ړ����x
const float  PlayerBase::RADIUS		 = 40.0f;						//���a�͈̔�
const VECTOR PlayerBase::POSITION	 = { 0.0f, 200.0f, 150.0f };	//���f���̈ʒu
const VECTOR PlayerBase::SIZE		 = { 0.4f, 0.4f, 0.4f };		//���f���{��
const VECTOR PlayerBase::UP			 = { 0, 1, 0 };					//�����
const VECTOR PlayerBase::DOWN		 = { 0,-1, 0 };					//������
const VECTOR PlayerBase::LEFT		 = {-1, 0, 0 };					//������
const VECTOR PlayerBase::RIGHT		 = { 1, 0, 0 };					//�E����
const int	 PlayerBase::UP_RANGE	 = 350;							//������̈ړ��͈�
const int	 PlayerBase::DOWN_RANGE  = 50;							//�������̈ړ��͈�
const int	 PlayerBase::LEFT_RANGE  = -410;						//�������̈ړ��͈�
const int	 PlayerBase::RIGHT_RANGE = 410;							//�E�����̈ړ��͈�
const int	 PlayerBase::AFTER_IMAGE_NUMBER = 3;					//�v���C���[�̎c������
const VECTOR PlayerBase::LING_ROTATE_SPEED = { 0.0f, 5.0f, 0.0f };			//�����O��]�X�s�[�h
const VECTOR PlayerBase::LING_SIZE		   = { -0.5f, -0.5f, -0.5f };		//�����O�{��


/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerBase::PlayerBase()
	: ObjectBase()
	, inputDirection()
	, inputFlag(false)
	, lingModel(0)
	, rotate()
	, rotateSpeed()
	, damageCount(0.0f)
	, noDrawFrame(false)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBase::~PlayerBase()
{
	//�����Ȃ�
}