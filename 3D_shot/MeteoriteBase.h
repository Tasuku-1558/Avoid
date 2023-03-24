#pragma once

#include "ObjectBase.h"

/// <summary>
/// ���e�I���C�g�x�[�X�N���X
/// </summary>
class MeteoriteBase : public ObjectBase
{
public:
	MeteoriteBase();
	virtual ~MeteoriteBase();

protected:
	
	int    random;			//�����_���l�̊i�[�p
	float  speed;			//�ړ����x
	bool   popFlag;			//覐Ώo���t���O
	VECTOR rotate;			//��]�l
	VECTOR rotateSpeed;		//��]���x


	//�萔
	const int    RANGE;				//�����_���l�͈̔�
	const float  SPEED;				//�ړ����x
	const float  MAX_ROTATE;		//�ő��]���x
	const float  POSITION_Z;		//Z���W
	const float  SPEED_UP;			//�ړ����x�A�b�v
	const VECTOR SIZE;				//�{��
	const VECTOR DIRECTION;			//����

};