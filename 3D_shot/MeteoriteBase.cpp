#include "MeteoriteBase.h"


const VECTOR MeteoriteBase::SIZE				   = { 0.3f, 0.3f, 0.3f };		//���f���{��
const VECTOR MeteoriteBase::DIR					   = { 0.0f, 0.0f, -1.0f };		//����
const float  MeteoriteBase::SPEED				   = 1500.0f;					//�ړ����x
const int	 MeteoriteBase::RANDOM_RANGE_X_OR_Y    = 400;						//X���W��Y���W�̃����_�����W
const float  MeteoriteBase::Z_POSITION			   = 1600.0f;					//Z���W
const int    MeteoriteBase::RANDOM_ROTATION_SPEED  = 400;						//�����_���ȉ�]�X�s�[�h
const int	 MeteoriteBase::RANGE				   = 2;							//�����_���l�͈̔�
const float  MeteoriteBase::SPEED_UP			   = 2500.0f;					//�ړ����x�A�b�v


/// <summary>
/// �R���X�g���N�^
/// </summary>
MeteoriteBase::MeteoriteBase()
	: rotateSpeed()
	, rotateAngle()
	, popFlag(true)
	, random(0)
	, speed(0.0f)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MeteoriteBase::~MeteoriteBase()
{
	//�����Ȃ�
}