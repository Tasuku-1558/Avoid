#include "MeteoriteBase.h"


const VECTOR MeteoriteBase::SIZE				   = VGet(0.3f, 0.3f, 0.3f);	//���f���{��
const float  MeteoriteBase::SPEED				   = 1500.0f;					//�ړ����x
const int	 MeteoriteBase::RANDOM_RANGE_X_OR_Y    = 450;						//X���W��Y���W�̃����_�����W
const float  MeteoriteBase::Z_POSITION			   = 1600.0f;					//Z���W
const VECTOR MeteoriteBase::DIR					   = VGet(0.0f, 0.0f, -1.0f);	//����
const int    MeteoriteBase::RANDOM_ROTATION_SPEED  = 400;						//�����_���ȉ�]�X�s�[�h
const float  MeteoriteBase::RADIUS				   = 65.0f;						//���a�͈̔�
const int    MeteoriteBase::METEORITE_ARRAY_NUMBER = 32;						//覐΂̔z��
const int	 MeteoriteBase::RANGE				   = 2;							//�����_���l�͈̔�


MeteoriteBase::MeteoriteBase()
	: rotateSpeed()
	, rotateAngle()
	, popFlag(true)
	, random(0)
{
	//�����Ȃ�
}

MeteoriteBase::~MeteoriteBase()
{
	//�����Ȃ�
}