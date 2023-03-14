#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player() : PlayerBase()
	, pastPosition()
	, emptyModel()
{
	state = State::NOMAL;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
	//�v���C���[���f���ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(modelHandle, SIZE);

	//�v���C���[�����O���f���ǂݍ���
	lingModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_LING));
	MV1SetScale(lingModel, LING_SIZE);

	//�v���C���[�c�����f���ǂݍ���
	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		emptyModel[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
		MV1SetScale(emptyModel[i], SIZE);
		MV1SetOpacityRate(emptyModel[i], 0.05f);
		MV1SetMaterialEmiColor(emptyModel[i], 0, GetColorF(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);

	MV1DeleteModel(lingModel);

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DeleteModel(emptyModel[i]);
	}
}

/// <summary>
/// ����������
/// </summary>
void Player::Activate()
{
	position = POSITION;

	rotate = ZERO_VECTOR;
	rotateSpeed = LING_ROTATE_SPEED;

	noDrawFrame = false;

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		pastPosition[i] = position;
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	//�v���C���[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);

	//�����O�̈ʒu�Ɖ�]�l���Z�b�g
	MV1SetPosition(lingModel, position);
	MV1SetRotationXYZ(lingModel, rotate);

	AfterImage();

	pUpdate(deltaTime);
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
void Player::Move(float deltaTime)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	rotate += rotateSpeed * deltaTime;
	
	//�㉺
	if (CheckHitKey(KEY_INPUT_UP))
	{
		//������̈ړ��͈͓��Ȃ�
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
		//�������̈ړ��͈͓��Ȃ�
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
		//�E�����̈ړ��͈͓��Ȃ�
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
		//�������̈ړ��͈͓��Ȃ�
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
/// <param name="deltaTime"></param>
void Player::pUpdate(float deltaTime)
{
	switch (state)
	{
	case State::NOMAL:
		break;

	case State::DAMAGE:
		OnHitMeteorite(deltaTime);
		break;
	}
}

/// <summary>
/// 覐΂ɓ��������Ȃ��
/// </summary>
/// <param name="deltaTime"></param>
void Player::OnHitMeteorite(float deltaTime)
{
	noDrawFrame = !noDrawFrame;			//2���1��`�悵�Ȃ�
	damageCount += deltaTime;

	//1�b�ԃv���C���[��_�ł�����
	if (damageCount > 1.0f)
	{
		state = State::NOMAL;
		noDrawFrame = false;
		damageCount = 0.0f;
	}
}

/// <summary>
/// �v���C���[�̎c������
/// </summary>
void Player::AfterImage()
{
	for (int i = 2; i >= 1; i--)
	{
		pastPosition[i] = pastPosition[i - 1];
		MV1SetPosition(emptyModel[i], pastPosition[i]);
	}

	pastPosition[0] = position;
	MV1SetPosition(emptyModel[0], pastPosition[0]);
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
	if (noDrawFrame == true)
	{
		return;
	}

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DrawModel(emptyModel[i]);
	}

	MV1DrawModel(modelHandle);
	
	MV1DrawModel(lingModel);
}