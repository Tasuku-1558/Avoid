#include "Meteorite.h"
#include "Player.h"
#include "ModelManager.h"
#include "Common.h"
#include <math.h>

using namespace Math3d;

Meteorite::Meteorite() : MeteoriteBase()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::METEORITE));
	MV1SetScale(modelHandle, SIZE);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [METEORITE]\n");
	}
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
	//�����Ȃ�
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
	Move(deltaTime, player);
	
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotateAngle);

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
	
	position += dir * deltaTime * SPEED;
	rotateAngle += rotateSpeed;
}

//�`�揈��
void Meteorite::Draw()
{
	MV1DrawModel(modelHandle);

	// �����蔻��f�o�b�O�`��i��ŏ����j
	//DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius, 8, GetColor(0, 255, 255), 0, FALSE);
}