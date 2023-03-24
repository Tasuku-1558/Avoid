#include "Meteorite.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "ModelManager.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
Meteorite::Meteorite()
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
	//覐΃��f���̓ǂݍ��݂ƃT�C�Y�̐ݒ�
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
	position = VGet((float)GetRand(400), (float)GetRand(400), POSITION_Z);

	random = rand() % RANGE;
	speed = SPEED;

	//�����_���ȉ�]���x��ݒ�
	rotateSpeed = VGet(GetRandf(0.0f, MAX_ROTATE), GetRandf(0.0f, MAX_ROTATE), GetRandf(0.0f, MAX_ROTATE));
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
	MV1SetRotationXYZ(modelHandle, rotate);

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