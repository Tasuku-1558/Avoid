#include "Player.h"
#include "Common.h"
#include "ModelManager.h"

using namespace Math3d;

//�R���X�g���N�^
Player::Player() : PlayerBase(ObjectTag::Player)
	, noDrawFrame(false)
	, damegeCount(0)
{
	state = State::Nomal;
}

//�f�X�g���N�^
Player::~Player()
{
	//�����Ȃ�
}

//����������
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(modelHandle, VGet(SIZE, SIZE, SIZE));
	
	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [PLAYER]\n");
	}
}

//����������
void Player::Activate()
{
	dir = VGet(0.0f, 0.0f, 1.0f);
	position = VGet(0.0f, 100.0f, -20.0f);

	// �����蔻�苅��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

//�X�V����
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	PUpdate(deltaTime);

	// mPosition , mDir ���L�����N�^�[�̈ʒu�E��]���Z�b�g
	MV1SetPosition(modelHandle, position);

	// �����蔻��̈ړ�
	collisionSphere.HitTestMove(position);
}

void Player::PUpdate(float deltaTime)
{
	switch (state)
	{
	case State::Miss:
		Damege(deltaTime);
		break;

	default:
		break;
	}
}

//�ړ�����
void Player::Move(float deltaTime)
{
	//�㉺���E����
	UP    = { 0, 1, 0 };
	DOWN  = { 0,-1, 0 };
	LEFT  = {-1, 0, 0 };
	RIGHT = { 1, 0, 0 };

	inputDirection = ZERO_VECTOR;

	inputFlag = false;
	
	//��������Ă������ɐi��
	if (CheckHitKey(KEY_INPUT_UP))
	{
		inputDirection += UP;
		inputFlag = true;
	}

	//���������Ă����牺�ɐi��
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		inputDirection += DOWN;
		inputFlag = true;
	}

	//�E�������Ă�����E�ɐi��
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		inputDirection += RIGHT;
		inputFlag = true;
	}

	//���������Ă����獶�ɐi��
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		inputDirection += LEFT;
		inputFlag = true;
	}
	
	//�\���L�[�̓��͂���������
	if (inputFlag)
	{
		//�\���L�[�̓��͕����𐳋K������
		inputDirection = VNorm(inputDirection);

		//�\���L�[�̈ړ������Ɉړ�������
		position += inputDirection * SPEED * deltaTime;
	}
}

//覐΂Ƃ̏Փˏ���
void Player::Damege(float deltaTime)
{
	noDrawFrame = !noDrawFrame;
	damegeCount += deltaTime;

	////�ʏ��Ԃ�
	//if (DamegeCount < 5.0)
	//{
	//	DamegeCount = 0.0f;
	//	NoDrawFrame = false;
	//}
}

//�`�揈��
void Player::Draw()
{
	MV1DrawModel(modelHandle);

	// �����蔻��f�o�b�O�`��i��ŏ����j
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);

	if (noDrawFrame)
	{
		return;
	}

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);
	DrawSphere3D(position, 39.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
}