#include "Meteorite.h"
#include "Player.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"
#include <math.h>

using namespace Math3d;

Meteorite::Meteorite() : MeteoriteBase()
{
	Initialize();
	Activate();
}

Meteorite::~Meteorite()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void Meteorite::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::METEORITE));
	MV1SetScale(modelHandle, SIZE);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [METEORITE]\n");
	}
}

/// <summary>
/// �I������
/// </summary>
void Meteorite::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// ����������
/// </summary>
void Meteorite::Activate()
{
	position = VGet(GetRand(RANDOM_RANGE_X_OR_Y), GetRand(RANDOM_RANGE_X_OR_Y), Z_POSITION);
	dir = DIR;
	random = rand() % RANGE;
	speed = SPEED;

	// �����_���ȉ�]�p���x���Z�b�g
	rotateSpeed = VGet(GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f);
	rotateAngle = ZERO_VECTOR;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void Meteorite::Update(float deltaTime, Player* player)
{
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
		dir = player->GetPosition() - position;

		if (VSize(dir) > 0.1f)
		{
			dir = VNorm(dir);
		}

		popFlag = false;
	}
	//�^����������
	else if(random == 1)
	{
		dir = DIR;
	}
	
	position += dir * deltaTime * speed;
	rotateAngle += rotateSpeed;
}

/// <summary>
/// �eWave�ł�覐΂̐F�ύX
/// </summary>
void Meteorite::RedColor()
{
	MV1SetDifColorScale(modelHandle, GetColorF(5.0f, 0.0f, 0.0f, 1.0f));
}

void Meteorite::YellowColor()
{
	MV1SetDifColorScale(modelHandle, GetColorF(50.0f, 50.0f, 0.0f, 1.0f));
}

void Meteorite::OrangeCollor()
{
	MV1SetDifColorScale(modelHandle, GetColorF(0.0f, 1.0f, 1.0f, 1.0f));
}

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