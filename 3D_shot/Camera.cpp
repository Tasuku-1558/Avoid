#include "Camera.h"

const float  Camera::NEAR_DISTANCE	  = 1.0f;						//�J�����ɉf���O�͈̔�
const float  Camera::FAR_DISTANCE	  = 3000.0f;					//�J�����ɉf��ŉ��͈̔�
const VECTOR Camera::INITIAL_POSITION = { 0.0f, 200.0f, -550.0f };	//�����ʒu
const VECTOR Camera::UP_VECTOR		  = { 0.0f, 200.0f, 0.0f };		//�J�����̏����

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Camera::Initialize()
{
	//�J�����̎�O�Ɖ��̋�����ݒ�
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);

	//�J�����̎��_�ƃ^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
}
