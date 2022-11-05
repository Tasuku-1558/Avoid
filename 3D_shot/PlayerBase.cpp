#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 400.0f;						//�ړ����x
const float  PlayerBase::RADIUS   = 40.0f;						//���a�͈̔�
const VECTOR PlayerBase::POSITION = VGet(0.0f, 200.0f, 160.0f); //���f���̈ʒu
const VECTOR PlayerBase::SIZE     = VGet(0.4f, 0.4f, 0.4f);		//���f���{��
const VECTOR PlayerBase::UP		  = VGet(0,  1, 0);				//�����
const VECTOR PlayerBase::DOWN	  = VGet(0, -1, 0);				//������
const VECTOR PlayerBase::LEFT	  = VGet(-1, 0, 0);				//������
const VECTOR PlayerBase::RIGHT    = VGet(1,  0, 0);				//�E����

PlayerBase::PlayerBase()
	: inputDirection()
	, inputFlag(false)
{
	//�����Ȃ�
}

PlayerBase::~PlayerBase()
{
	//�����Ȃ�
}
