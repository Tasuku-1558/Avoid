#include "Player.h"
#include "Common.h"
#include "ModelManager.h"

using namespace Math3d;

//�R���X�g���N�^
Player::Player() : PlayerBase(ObjectTag::Player)
	
{
	//�����Ȃ�
}

//�f�X�g���N�^
Player::~Player()
{
	//�����Ȃ�
}

//����������
void Player::Initialize()
{
	ModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(ModelHandle, VGet(SIZE, SIZE, SIZE));

	//�ǂݍ��ݎ��s�ŃG���[
	if (ModelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [PLAYER]\n");
	}
	
	Dir = VGet(0.0f, 0.0f, 1.0f);
	Position = VGet(0.0f, 100.0f, -20.0f);

	// �����蔻�苅��ݒ�
	CollisionSphere.LocalCenter = VGet(0, 0, 0);
	CollisionSphere.WorldCenter = Position;
	CollisionSphere.Radius = RADIUS;
}

//�X�V����
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	// mPosition , mDir ���L�����N�^�[�̈ʒu�E��]���Z�b�g
	MV1SetPosition(ModelHandle, Position);

	// �����蔻��̈ړ�
	CollisionSphere.HitTestMove(Position);
}

//�ړ�����
void Player::Move(float deltaTime)
{
	//�㉺���E����
	UP    = { 0, 1, 0 };
	DOWN  = { 0,-1, 0 };
	LEFT  = { -1,0, 0 };
	RIGHT = { 1, 0, 0 };

	InputDirection = ZERO_VECTOR;

	InputFlag = false;

	//��������Ă������ɐi��
	if (CheckHitKey(KEY_INPUT_UP))
	{
		InputDirection += UP;
		InputFlag = true;
	}

	//���������Ă����牺�ɐi��
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		InputDirection += DOWN;
		InputFlag = true;
	}
	
	//�E�������Ă�����E�ɐi��
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		InputDirection += RIGHT;
		InputFlag = true;
	}

	//���������Ă����獶�ɐi��
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		InputDirection += LEFT;
		InputFlag = true;
	}
	
	//�\���L�[�̓��͂���������
	if (InputFlag)
	{
		//�\���L�[�̓��͕����𐳋K������
		InputDirection = VNorm(InputDirection);

		//�\���L�[�̈ړ������Ɉړ�������
		Position += InputDirection * SPEED * deltaTime;
	}
}

//�`�揈��
void Player::Draw()
{
	MV1DrawModel(ModelHandle);

	// �����蔻��f�o�b�O�`��i��ŏ����j
	DrawSphere3D(CollisionSphere.WorldCenter, CollisionSphere.Radius,
		8, GetColor(0, 255, 0), 0, FALSE);
}