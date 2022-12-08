#include "Player.h"
#include "Common.h"
#include "ModelManager.h"

using namespace Math3d;

const VECTOR Player::LING_ROTATE	   = { 0.0f, 1.0f, 0.0f };		//�����O�{��
const VECTOR Player::LING_ROTATE_SPEED = { 0.0f, 5.0f, 0.0f };		//�����O��]�p�x
const VECTOR Player::LING_SIZE		   = { -0.5f, -0.5f, -0.5f };	//�����O��]�X�s�[�h

//�R���X�g���N�^
Player::Player() : PlayerBase()
	, lingModel(0)
	, rotate()
	, rotate_Speed()
	, damageCount(0)
	, noDrawFrame(false)
{
	state = State::Nomal;
}

//�f�X�g���N�^
Player::~Player()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL || lingModel != NULL)
	{
		Finalize();
	}
}

//����������
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(modelHandle, SIZE);
	
	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [PLAYER]\n");
	}

	lingModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_LING));
	MV1SetScale(lingModel, LING_SIZE);

	if (lingModel < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [PLAYER_LING]\n");
	}
}

//�I������
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(lingModel);
	lingModel = NULL;
}

//����������
void Player::Activate()
{
	position = POSITION;

	// �����蔻�苅��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius		= RADIUS;

	rotate = LING_ROTATE;
	rotate_Speed = LING_ROTATE_SPEED;

	noDrawFrame = false;
}

//�X�V����
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	// �v���C���[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);

	// �����蔻��̈ړ�
	collisionSphere.HitTestMove(position);

	MV1SetPosition(lingModel, position);
	MV1SetRotationXYZ(lingModel, rotate);
	
}

//�ړ�����
void Player::Move(float deltaTime)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	rotate += rotate_Speed * deltaTime;
	
	//�㉺
	if (CheckHitKey(KEY_INPUT_UP))
	{
		if (position.y < 350)
		{
			inputDirection.y += 1.0f;
			inputFlag = true;
		}
		else
		{
			inputDirection.y = 0.0f;
		}
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (position.y > 50)
		{
			inputDirection.y -= 1.0f;
			inputFlag = true;
		}
		else
		{
			inputDirection.y = 0.0f;
		}
	}
	//���E
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		if (position.x < 410)
		{
			inputDirection.x += 1.0f;
			inputFlag = true;
		}
		else
		{
			inputDirection.x = 0.0f;
		}
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		if (position.x > -410)
		{
			inputDirection.x -= 1.0f;
			inputFlag = true;
		}
		else
		{
			inputDirection.x = 0.0f;
		}
	}
	
	//�\���L�[�̓��͂���������
	if (inputFlag)
	{
		//�\���L�[�̓��͕����𐳋K��
		inputDirection = VNorm(inputDirection);

		//�\���L�[�̈ړ������Ɉړ�
		position += inputDirection * SPEED * deltaTime;
	}
}

void Player::pUpdate()
{
	switch (state)
	{
	case State::Nomal:
		break;

	case State::Damage:
		OnHitMeteorite();
		break;
	}
}

//覐΂ɓ�������
void Player::OnHitMeteorite()
{
	noDrawFrame = !noDrawFrame;			//2���1��`�悵�Ȃ�
	damageCount += 1;

	if (damageCount > 10)
	{
		state = State::Nomal;
		noDrawFrame = false;
		damageCount = 0;
	}
}

//�`�揈��
void Player::Draw()
{
	pUpdate();

	if (noDrawFrame == true)
	{
		return;
	}

	MV1DrawModel(modelHandle);
	
	MV1DrawModel(lingModel);
}