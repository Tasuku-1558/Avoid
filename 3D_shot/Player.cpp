#include "Player.h"
#include "Common.h"
#include "ModelManager.h"

using namespace Math3d;

//�R���X�g���N�^
Player::Player() : PlayerBase()
{
	//�����Ȃ�
}

//�f�X�g���N�^
Player::~Player()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL)
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
}

//�I������
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

//����������
void Player::Activate()
{
	position = POSITION;

	// �����蔻�苅��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius		= RADIUS;
}

//�X�V����
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	// �v���C���[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);

	// �����蔻��̈ړ�
	collisionSphere.HitTestMove(position);
}

//�ړ�����
void Player::Move(float deltaTime)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;
	
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
	if (CheckHitKey(KEY_INPUT_DOWN))
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
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		if (position.x < 480)
		{
			inputDirection.x += 1.0f;
			inputFlag = true;
		}
		else
		{
			inputDirection.x = 0.0f;
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		if (position.x > -500)
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

//�`�揈��
void Player::Draw()
{
	MV1DrawModel(modelHandle);

	// �����蔻��f�o�b�O�p�`��
	//DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius, 8, GetColor(0, 255, 0), 0, FALSE);
}