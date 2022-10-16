#include "MeteoriteBase.h"

const float MeteoriteBase::SIZE					  = 0.3f;		//���f���{��
const float MeteoriteBase::SPEED				  = 700.0f;		//�ړ����x
const int	MeteoriteBase::RANDOM_RANGE_X_OR_Y	  = 450;		//X���W��Y���W�̃����_�����W
const float MeteoriteBase::Z_POSITION			  = 1600.0f;	//Z���W
const int   MeteoriteBase::RANDOM_ROTATION_SPEED  = 400;		//�����_���ȉ�]�X�s�[�h
const float MeteoriteBase::RADIUS				  = 65.0f;		//���a�͈̔�
const int   MeteoriteBase::METEORITE_ARRAY_NUMBER = 20;			//覐΂̔z��


MeteoriteBase::MeteoriteBase(ObjectTag tag)
	: Tag(tag)
	, RotateSpeed()
	, RotateAngle()
	/*, PopCount(0.0f)*/
	, PopFlag(true)
{
	//�����Ȃ�
}

MeteoriteBase::~MeteoriteBase()
{
	//�����Ȃ�
}