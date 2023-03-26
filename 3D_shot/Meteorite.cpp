#include "Meteorite.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "ModelManager.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player"></param>
Meteorite::Meteorite(Player* player)
{
	Initialize();

	playerPosition = player->GetPosition();
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

	randomDirection = rand() % RANGE_DIRECTION;
	speed = SPEED;

	//�����_���ȉ�]���x��ݒ�
	rotateSpeed = VGet(GetRandf(0.0f, MAX_ROTATE), GetRandf(0.0f, MAX_ROTATE), GetRandf(0.0f, MAX_ROTATE));

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
/// <param name="deltaTime"></param>
void Meteorite::Update(float deltaTime)
{
	//覐΂̈ʒu�Ɖ�]�l���Z�b�g
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotate);

	Move(deltaTime);
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
void Meteorite::Move(float deltaTime)
{
	//�����_���l��0�ŏo���t���O��true�Ȃ�
	//�v���C���[�Ɍ������Ē���
	if (popFlag && randomDirection == 0)
	{
		//�v���C���[����覐΂̍��W���������l���擾
		direction = playerPosition - position;

		if (VSize(direction) > 0.1f)
		{
			direction = VNorm(direction);
		}

		popFlag = false;
	}

	//�����_���l��1�Ȃ�
	//�^����������
	else if(randomDirection == 1)
	{
		direction = DIRECTION;
	}
	
	position += direction * deltaTime * speed;
	rotate += rotateSpeed;
}

/// <summary>
/// �eWave�ł�覐΂̐F�ύX
/// </summary>
void Meteorite::ChangeColor(float red, float green, float blue)
{
	MV1SetDifColorScale(modelHandle, GetColorF(red, green, blue, 1.0f));
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