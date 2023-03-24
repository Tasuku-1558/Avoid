#include "Camera.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
	: NEAR_DISTANCE(1.0f)
	, FAR_DISTANCE(3000.0f)
	, INITIAL_POSITION({ 0.0f, 200.0f, -550.0f })
	, UP_VECTOR({ 0.0f, 200.0f, 0.0f })
{
	Initialize();
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
