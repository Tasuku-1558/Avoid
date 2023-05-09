#include "Meteorite.h"
#include "ModelManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="inPlayerPosition">�v���C���[�̍��W</param>
Meteorite::Meteorite(VECTOR inPlayerPosition)
{
	Initialize();

	playerPosition = inPlayerPosition;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Meteorite::~Meteorite()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void Meteorite::Initialize()
{
	//覐΃��f���̓ǂݍ��݂ƃT�C�Y�̐ݒ�
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::METEORITE));
	MV1SetScale(modelHandle, SIZE);

	//覐΂̈ʒu�������_���l��
	position = RANDOM_POSITION;

	//覐΂��i�ޕ����Ƀ����_���l������
	randomDirection = rand() % RANGE_DIRECTION;

	speed = SPEED;

	//�����_���ȉ�]���x��ݒ�
	rotateSpeed = RANDOM_ROTATE_SPEED;
}

/// <summary>
/// �I������
/// </summary>
void Meteorite::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Meteorite::Update(float deltaTime)
{
	Move(deltaTime);
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Meteorite::Move(float deltaTime)
{
	//�����_���l��0�ŏo���t���O��true�Ȃ�
	//�v���C���[�Ɍ������Ē���
	if (popFlag && randomDirection == TRACKING_VALUE)
	{
		//�v���C���[����覐΂̍��W���������l���擾
		direction = playerPosition - position;

		popFlag = false;
	}

	//�����_���l��1�Ȃ�
	//�^����������
	else if(randomDirection == STRAIGHT_VALUE)
	{
		direction = DIRECTION;
	}

	//�x�N�g���̐��K��
	direction = VNorm(direction);
	
	position += direction * speed * deltaTime;
	rotate += rotateSpeed;

	//覐΂̈ʒu�Ɖ�]�l���Z�b�g
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotate);
}

/// <summary>
/// 覐΂̃X�s�[�h�ω�
/// </summary>
void Meteorite::SpeedUp()
{
	speed = SPEED_UP;
}

/// <summary>
/// �`�揈��
/// </summary>
void Meteorite::Draw()
{
	MV1DrawModel(modelHandle);
}