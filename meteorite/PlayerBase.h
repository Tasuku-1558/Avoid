#pragma once

#include "ObjectBase.h"

//Player�̐e�N���X
//ObjectBase���p��


class PlayerBase : public ObjectBase
{
public:
	PlayerBase(ObjectTag tag);
	virtual ~PlayerBase();



protected:
	ObjectTag Tag;					//�I�u�W�F�N�g���
	VECTOR InputDirection;			//���͂��ꂽ����
	VECTOR UP;						//�����
	VECTOR DOWN;					//������
	VECTOR LEFT;					//������
	VECTOR RIGHT;					//�E����
	bool InputFlag;					//�L�[���̓t���O


	//�ÓI�萔
	static const float SIZE;		//���f���{��
	static const float SPEED;		//�ړ����x
	static const float RADIUS;		//���a�͈̔�

};