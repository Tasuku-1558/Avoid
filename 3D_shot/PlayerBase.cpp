#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 400.0f;						//�ړ����x
const float  PlayerBase::RADIUS   = 40.0f;						//���a�͈̔�
const VECTOR PlayerBase::POSITION = { 0.0f, 200.0f, 150.0f };	//���f���̈ʒu
const VECTOR PlayerBase::SIZE	  = { 0.4f, 0.4f, 0.4f };		//���f���{��
const VECTOR PlayerBase::UP		  = { 0, 1, 0 };				//�����
const VECTOR PlayerBase::DOWN	  = { 0,-1, 0 };				//������
const VECTOR PlayerBase::LEFT	  = {-1, 0, 0 };				//������
const VECTOR PlayerBase::RIGHT	  = { 1, 0, 0 };				//�E����


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
