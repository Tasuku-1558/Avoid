#pragma once

#include "ObjectBase.h"

//Player�̐e�N���X
//ObjectBase���p��

class PlayerBase : public ObjectBase
{
public:
			 PlayerBase();
	virtual ~PlayerBase();

protected:
	VECTOR inputDirection;			//���͂��ꂽ����
	bool   inputFlag;				//�L�[���̓t���O
	int    lingModel;				//�����O���f���i�[�p
	VECTOR rotate;					//�����O��]
	VECTOR rotate_Speed;			//�����O��]�X�s�[�h
	int    damageCount;				//�_���[�W���ԃJ�E���g
	bool   noDrawFrame;				//���f����2��ɂP��͕`�悵�Ȃ�



	//�ÓI�萔
	static const float SPEED;		//�ړ����x
	static const float RADIUS;		//���a�͈̔�
	static const VECTOR POSITION;	//���f���̈ʒu
	static const VECTOR SIZE;		//���f���{��
	static const VECTOR UP;			//�����
	static const VECTOR DOWN;		//������
	static const VECTOR LEFT;		//������
	static const VECTOR RIGHT;		//�E����
	static const int	UP_RANGE;	//������̈ړ��͈�
	static const int    DOWN_RANGE; //�������̈ړ��͈�
	static const int    LEFT_RANGE; //�������̈ړ��͈�
	static const int    RIGHT_RANGE;//�E�����̈ړ��͈�
	static const VECTOR LING_SIZE;				//�����O�{��
	static const VECTOR LING_ROTATE;			//�����O��]�X�s�[�h
	static const VECTOR LING_ROTATE_SPEED;		//�����O�T�C�Y

};