#pragma once

#include "ObjectBase.h"

/// <summary>
/// 覐Ί��N���X
/// </summary>
class MeteoriteBase : public ObjectBase
{
public:
	MeteoriteBase();
	virtual ~MeteoriteBase();

protected:
	
	int    randomDirection;	//覐΂��i�ޕ����̃����_���l�̊i�[�p
	float  speed;			//�ړ����x
	bool   popFlag;			//覐Ώo���t���O
	VECTOR playerPosition;	//�v���C���[�̈ʒu
	VECTOR rotate;			//��]�l
	VECTOR rotateSpeed;		//��]���x


	//�萔
	const int    RANGE_DIRECTION;	//覐΂��i�ޕ����̃����_���l�͈̔�
	const float  SPEED;				//�ړ����x
	const float  MAX_ROTATE;		//�ő��]���x
	const float  SPEED_UP;			//�ړ����x�A�b�v
	const VECTOR RANDOM_POSITION;	//�����_���ȏo���ʒu
	const VECTOR SIZE;				//�{��
	const VECTOR DIRECTION;			//����

};