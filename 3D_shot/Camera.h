#pragma once

#include "DxLib.h"

/// <summary>
/// �J�����N���X
/// �Œ�^�J����
/// </summary>
class Camera final
{
public: 
	Camera();
	virtual ~Camera();

private:
	Camera(const Camera&);						//�R�s�[�R���X�g���N�^

	void Initialize();

	//�萔
	static const float  NEAR_DISTANCE;		//�J�����ɉf���O�͈̔�
	static const float  FAR_DISTANCE;		//�J�����ɉf��ŉ��͈̔�
	static const VECTOR INITIAL_POSITION;	//�����ʒu
	static const VECTOR UP_VECTOR;			//�J�����̏����
};