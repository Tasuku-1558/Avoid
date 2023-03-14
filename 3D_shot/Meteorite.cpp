#include "Meteorite.h"
#include "Player.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
Meteorite::Meteorite()
	: MeteoriteBase()
{
	Initialize();
	Activate();
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
	//覐΃��f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::METEORITE));
	MV1SetScale(modelHandle, SIZE);
}

/// <summary>
/// �I������
/// </summary>
void Meteorite::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// ����������
/// </summary>
void Meteorite::Activate()
{
	//覐΂̈ʒu�Ƀ����_���l������
	position = VGet(GetRand(RANDOM_RANGE_X_OR_Y), GetRand(RANDOM_RANGE_X_OR_Y), Z_POSITION);

	direction = DIRECTION;
	random = rand() % RANGE;
	speed = SPEED;

	//�����_���ȉ�]�p���x���Z�b�g
	rotateSpeed = VGet(GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void Meteorite::Update(float deltaTime, Player* player)
{
	//覐΂̈ʒu�Ɖ�]�l���Z�b�g
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotateAngle);

	Move(deltaTime, player);
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void Meteorite::Move(float deltaTime, Player* player)
{
	//�v���C���[�Ɍ������Ē���
	if (popFlag && random == 0)
	{
		direction = player->GetPosition() - position;

		if (VSize(direction) > 0.1f)
		{
			direction = VNorm(direction);
		}

		popFlag = false;
	}

	//�^����������
	else if(random == 1)
	{
		direction = DIRECTION;
	}
	
	position += direction * deltaTime * speed;
	rotateAngle += rotateSpeed;
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