#pragma once

#include "ObjectBase.h"

//Meteorite�̐e�N���X
//ObjectBase���p��


class MeteoriteBase : public ObjectBase
{
public:
			 MeteoriteBase();
	virtual ~MeteoriteBase();

protected:
	
	VECTOR rotateSpeed;							//��]���x x,y,z
	VECTOR rotateAngle;							//��]�p x,y,z
	bool   popFlag;								//覐Ώo���t���O
	int    random;								//覐΂̃����_���l
	float  speed;								//覐΂̑��x
	int    shadowMapHandle;						//�V���h�E�}�b�v�i�[�p



	//�ÓI�萔
	static const VECTOR SIZE;					//���f���{��
	static const float  SPEED;					//�ړ����x
	static const int    RANDOM_RANGE_X_OR_Y;	//X���W��Y���W�̃����_�����W
	static const float  Z_POSITION;				//Z���W
	static const VECTOR DIR;					//����
	static const int    RANDOM_ROTATION_SPEED;	//�����_���ȉ�]�X�s�[�h
	static const int    RANGE;					//�����_���l�͈̔�
	static const float  SPEED_UP;				//�ړ����x�A�b�v
};