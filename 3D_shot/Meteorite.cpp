#include "Player.h"
#include "Meteorite.h"
#include "ModelManager.h"
#include <math.h>

using namespace Math3d;


Meteorite::Meteorite() : MeteoriteBase(ObjectTag::Meteorite)
{
	//�����Ȃ�
}

Meteorite::~Meteorite()
{
	//�����Ȃ�
}

//����������
void Meteorite::Initialize()
{
	ModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::METEORITE));
	MV1SetScale(ModelHandle, VGet(SIZE, SIZE, SIZE));

	//�ǂݍ��ݎ��s�ŃG���[
	if (ModelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [METEORITE]\n");
	}

	Position = VGet(/*GetRand(RANDOM_RANGE_X_OR_Y), GetRand(RANDOM_RANGE_X_OR_Y)*/0.0f,100.0f, Z_POSITION);
	Dir = VGet(0.0f, 0.0f, -1.0f);

	// �����_���ȉ�]�p���x���Z�b�g
	RotateSpeed = VGet(GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f);
	RotateAngle = VGet(0, 0, 0);

	// �����蔻�苅��ݒ�
	CollisionSphere.LocalCenter = VGet(0, 0, 0);
	CollisionSphere.Radius = RADIUS;
	CollisionSphere.WorldCenter = Position;
}

//�X�V����
void Meteorite::Update(float deltaTime, Player* player)
{
	Move(deltaTime, player);

	MV1SetPosition(ModelHandle, Position);
	MV1SetRotationXYZ(ModelHandle, RotateAngle);

	// �����蔻��̈ړ�
	CollisionSphere.HitTestMove(Position);
}

//�ړ�����
void Meteorite::Move(float deltaTime, Player* player)
{
	
	/*if (PopFlag)
	{
		Dir = player->GetPosition() - Position;

		if (VSize(Dir) > 0.1f)
		{
			Dir = VNorm(Dir);
		}
		PopFlag = false;
	}*/
	/*else if()
	{
		Dir = VGet(10.0f,10.0f,0.0f);
		if (VSize(Dir) > 0.1f)
		{
			Dir = VNorm(Dir);
		}
	}*/
	
	
	Position += Dir * deltaTime * SPEED;
	RotateAngle += RotateSpeed;
}

//�`�揈��
void Meteorite::Draw()
{
	MV1DrawModel(ModelHandle);

	// �����蔻��f�o�b�O�`��i��ŏ����j
	DrawSphere3D(CollisionSphere.WorldCenter, CollisionSphere.Radius, 8, GetColor(0, 255, 255), 0, FALSE);
}

//覐Ώo���J�E���g
//void Meteorite::MeteoritePopCount(float deltaTime)
// {
//	PopCount += deltaTime;
//
//	if (PopCount > 1.0)
//	{
//		PopCount = 0.0f;
//	}
//}