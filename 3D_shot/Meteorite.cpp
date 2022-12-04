#include "Meteorite.h"
#include "Player.h"
#include "ModelManager.h"
#include "Common.h"
#include <math.h>

using namespace Math3d;

Meteorite::Meteorite() : MeteoriteBase()
	, shadowMapHandle(0)
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

//����������
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

//�I������
void Meteorite::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

//����������
void Meteorite::Activate()
{
	position = VGet(GetRand(RANDOM_RANGE_X_OR_Y), GetRand(RANDOM_RANGE_X_OR_Y), Z_POSITION);
	dir = DIR;
	random = rand() % RANGE;
	speed = SPEED;

	// �����_���ȉ�]�p���x���Z�b�g
	rotateSpeed = VGet(GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f);
	rotateAngle = ZERO_VECTOR;

	// �����蔻�苅��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius		= RADIUS;
}

//�X�V����
void Meteorite::Update(float deltaTime, Player* player)
{
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotateAngle);

	Move(deltaTime, player);
	
	// �����蔻��̈ړ�
	collisionSphere.HitTestMove(position);
}

//�ړ�����
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

void Meteorite::SpeedUp()
{
	//speed = 2000.0f;
}

//�`�揈��
void Meteorite::Draw()
{
	MV1DrawModel(modelHandle);
}