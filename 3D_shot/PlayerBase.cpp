#include "PlayerBase.h"


const float PlayerBase::SIZE   = 0.4f;		//���f���{��
const float PlayerBase::SPEED  = 400.0f;	//�ړ����x
const float PlayerBase::RADIUS = 41.0f;		//���a�͈̔�


PlayerBase::PlayerBase(ObjectTag tag)
	: Tag(tag)
	, inputDirection()
	, inputFlag(false)
	, UP()
	, DOWN()
	, LEFT()
	, RIGHT()
{
	//�����Ȃ�
}

PlayerBase::~PlayerBase()
{
	//�����Ȃ�
}
