#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"

using namespace Math3d;


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player() : PlayerBase()
{
	state = State::NOMAL;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL || lingModel != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
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

/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(lingModel);
	lingModel = NULL;
}

/// <summary>
/// ����������
/// </summary>
void Player::Activate()
{
	position = POSITION;

	rotate = LING_ROTATE;
	rotate_Speed = LING_ROTATE_SPEED;

	noDrawFrame = false;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	// �v���C���[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);

	MV1SetPosition(lingModel, position);
	MV1SetRotationXYZ(lingModel, rotate);
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
void Player::Move(float deltaTime)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	rotate += rotate_Speed * deltaTime;
	
	//�㉺
	if (CheckHitKey(KEY_INPUT_UP))
	{
		if (position.y < UP_RANGE)
		{
			inputDirection += UP;
			inputFlag = true;
		}
		else
		{
			inputDirection = ZERO_VECTOR;
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (position.y > DOWN_RANGE)
		{
			inputDirection += DOWN;
			inputFlag = true;
		}
		else
		{
			inputDirection = ZERO_VECTOR;
		}
	}
	//���E
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		if (position.x < RIGHT_RANGE)
		{
			inputDirection += RIGHT;
			inputFlag = true;
		}
		else
		{
			inputDirection = ZERO_VECTOR;
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		if (position.x > LEFT_RANGE)
		{
			inputDirection += LEFT;
			inputFlag = true;
		}
		else
		{
			inputDirection = ZERO_VECTOR;
		}
	}
	
	//�\���L�[�̓��͂���������
	if (inputFlag)
	{
		// ���E�E�㉺���������Ȃǂœ��̓x�N�g����0�̎�
		if (VSquareSize(inputDirection) < 1.0f)
		{
			return;
		}

		//�\���L�[�̓��͕����𐳋K��
		inputDirection = VNorm(inputDirection);

		//�\���L�[�̈ړ������Ɉړ�
		position += inputDirection * SPEED * deltaTime;
	}
}

/// <summary>
/// �v���C���[�̏��
/// </summary>
void Player::pUpdate()
{
	switch (state)
	{
	case State::NOMAL:
		break;

	case State::DAMAGE:
		OnHitMeteorite();
		break;
	}
}

/// <summary>
/// 覐΂ɓ��������Ȃ��
/// </summary>
void Player::OnHitMeteorite()
{
	noDrawFrame = !noDrawFrame;			//2���1��`�悵�Ȃ�
	damageCount += 1;

	if (damageCount > 10)
	{
		state = State::NOMAL;
		noDrawFrame = false;
		damageCount = 0;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
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