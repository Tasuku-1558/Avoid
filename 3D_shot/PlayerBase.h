#pragma once

#include "ObjectBase.h"

/// <summary>
/// �v���C���[���N���X
/// </summary>
class PlayerBase : public ObjectBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

protected:

	int    lingModel;					//�����O���f���i�[�p
	int	   afterImageModelHandle[10];	//�c�����f���i�[�p
	float  damageTime;					//�_���[�W���ԃJ�E���g
	bool   inputFlag;					//�L�[���̓t���O
	bool   noDrawFrame;					//���f����2��ɂP��͕`�悵�Ȃ�
	VECTOR inputDirection;				//���͂��ꂽ����
	VECTOR rotate;						//�����O��]
	VECTOR rotateSpeed;					//�����O��]�X�s�[�h
	VECTOR pastPosition[10];			//�v���C���[�̉ߋ��̈ʒu


	//�萔
	const int	  UP_RANGE;				//������̈ړ��͈�
	const int     DOWN_RANGE;			//�������̈ړ��͈�
	const int     LEFT_RANGE;			//�������̈ړ��͈�
	const int     RIGHT_RANGE;			//�E�����̈ړ��͈�
	const int	  AFTER_IMAGE_NUMBER;	//�v���C���[�̎c������
	const float   SPEED;				//�ړ����x
	const float	  OPACITY;				//�s�����x
	const float   RADIUS;				//���a�͈̔�
	const float   MAX_FLASH_TIME;		//�ő�_�Ŏ���
	const float	  INITIAL_DAMAGE_TIME;	//�����̃_���[�W����
	const float	  MAX_INPUT_DIRECTION;	//�ő���̓x�N�g��
	const VECTOR  POSITION;				//�ʒu
	const VECTOR  SIZE;					//�{��
	const VECTOR  UP;					//�����
	const VECTOR  DOWN;					//������
	const VECTOR  LEFT;					//������
	const VECTOR  RIGHT;				//�E����
	const VECTOR  LING_SIZE;			//�����O�{��
	const VECTOR  LING_ROTATE_SPEED;	//�����O��]�X�s�[�h
	const COLOR_F AFTER_IMAGE_COLOR;	//�c�����f���̃G�~�b�V�u�J���[

};