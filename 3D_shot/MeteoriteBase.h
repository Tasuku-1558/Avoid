#pragma once

#include "ObjectBase.h"

//Meteorite�̐e�N���X
//ObjectBase���p��


class MeteoriteBase : public ObjectBase
{
public:
			 MeteoriteBase(ObjectTag tag);
	virtual ~MeteoriteBase();

	static const int METEORITE_ARRAY_NUMBER;	//覐΂̔z��

protected:
	ObjectTag Tag;								//�I�u�W�F�N�g���
	VECTOR RotateSpeed;							//��]���x x,y,z
	VECTOR RotateAngle;							//��]�p x,y,z
	//float  PopCount;							//覐Ώo���J�E���g
	bool   PopFlag;								//覐Ώo���t���O

	//�ÓI�萔
	static const float SIZE;					//���f���{��
	static const float SPEED;					//�ړ����x
	static const int   RANDOM_RANGE_X_OR_Y;		//X���W��Y���W�̃����_�����W
	static const float Z_POSITION;				//Z���W
	static const int   RANDOM_ROTATION_SPEED;	//�����_���ȉ�]�X�s�[�h
	static const float RADIUS;					//���a�͈̔�
	
};