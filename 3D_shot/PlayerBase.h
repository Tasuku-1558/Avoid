#pragma once

#include "ObjectBase.h"

/// <summary>
/// Player�̐e�N���X
/// ObjectBase���p��
/// </summary>
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
	VECTOR rotateSpeed;				//�����O��]�X�s�[�h
	float  damageCount;				//�_���[�W���ԃJ�E���g
	bool   noDrawFrame;				//���f����2��ɂP��͕`�悵�Ȃ�


	//�萔
	static const float SPEED;		//�ړ����x
	const float	  OPACITY;			//�s�����x
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
	static const int AFTER_IMAGE_NUMBER;	//�v���C���[�̎c������
	const COLOR_F AFTER_IMAGE_COLOR;			//�c�����f���̃G�~�b�V�u�J���[


	static const VECTOR LING_SIZE;				//�����O�{��
	static const VECTOR LING_ROTATE_SPEED;		//�����O��]�X�s�[�h

};