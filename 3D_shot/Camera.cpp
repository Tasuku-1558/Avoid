#include "Camera.h"

const float  Camera::NEAR_DISTANCE	  = 1.0f;						//�J�����ɉf���O�͈̔�
const float  Camera::FAR_DISTANCE	  = 2000.0f;					//�J�����ɉf��ŉ��͈̔�
const VECTOR Camera::INITIAL_POSITION = { 0.0f, 200.0f, -550.0f };	//�����ʒu
const VECTOR Camera::UP_VECTOR		  = { 0.0f, 200.0f, 0.0f };		//�J�����̏����

Camera::Camera()
{
	//�����Ȃ�
}

Camera::~Camera()
{
	//�����Ȃ�
}

void Camera::Update()
{
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	//�J�����̎�O�Ɖ��̋�����ݒ肷��
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);

	//�J����(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
}
