#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
	: playerState(PlayerState::NOMAL)
{
	Initialize();
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
	//�v���C���[���f���̓ǂݍ��݂ƃT�C�Y�̐ݒ�
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(modelHandle, SIZE);
	position = POSITION;

	//�v���C���[�����O���f���̓ǂݍ��݂ƃT�C�Y�̐ݒ�
	lingModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_LING));
	MV1SetScale(lingModel, LING_SIZE);
	rotateSpeed = LING_ROTATE_SPEED;

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		//�v���C���[�c�����f���̓ǂݍ��݂ƃT�C�Y�̐ݒ�
		afterImageModelHandle[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
		MV1SetScale(afterImageModelHandle[i], SIZE);

		//���f���̕s�����x�̐ݒ�
		//0.0f�ɋ߂��قǓ����x���オ��
		MV1SetOpacityRate(afterImageModelHandle[i], OPACITY);

		//���f���̃G�~�b�V�u�J���[��ύX
		MV1SetMaterialEmiColor(afterImageModelHandle[i], 0, AFTER_IMAGE_COLOR);

		pastPosition[i] = POSITION;
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
		MV1DeleteModel(afterImageModelHandle[i]);
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	AfterImage();

	HitMeteorite(deltaTime);
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
void Player::Move(float deltaTime)
{
	//���͕���������������
	inputDirection = ZERO_VECTOR;

	rotate += rotateSpeed * deltaTime;
	
	KeyInput();
	
	//�\���L�[�̓��͂���������
	if (inputFlag)
	{
		// ���E�E�㉺���������Ȃǂœ��̓x�N�g����0�̎�
		if (VSquareSize(inputDirection) < 1.0f)
		{
			return;
		}

		//�\���L�[�̓��͕����𐳋K��
		direction = VNorm(inputDirection);

		//�\���L�[�̈ړ������Ɉړ�
		position += direction * SPEED * deltaTime;
	}

	//�v���C���[���f���̈ʒu��ݒ�
	MV1SetPosition(modelHandle, position);

	//�v���C���[�����O���f���̈ʒu�Ɖ�]�l��ݒ�
	MV1SetPosition(lingModel, position);
	MV1SetRotationXYZ(lingModel, rotate);
}

/// <summary>
/// �L�[���͏���
/// </summary>
void Player::KeyInput()
{
	//�㉺�ړ�
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
	//���E�ړ�
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
}

/// <summary>
/// 覐΂ɏՓ˂���
/// </summary>
/// <param name="deltaTime"></param>
void Player::HitMeteorite(float deltaTime)
{
	//�v���C���[�̏�Ԃ���e��ԂȂ�
	if (playerState == PlayerState::DAMAGE)
	{
		//2���1��`�悵�Ȃ�
		noDrawFrame = !noDrawFrame;

		//�_���[�W�J�E���g���J�n����
		damageCount += deltaTime;

		//1�b�ԃv���C���[��_�ł�����
		if (damageCount > FLASH_TIME)
		{
			//�ʏ��Ԃ֖߂�
			playerState = PlayerState::NOMAL;

			noDrawFrame = false;
			damageCount = 0.0f;
		}
	}
}

/// <summary>
/// �v���C���[�̎c������
/// </summary>
void Player::AfterImage()
{
	for (int i = AFTER_IMAGE_NUMBER - 1; i >= 1; i--)
	{
		pastPosition[i] = pastPosition[i - 1];
		MV1SetPosition(afterImageModelHandle[i], pastPosition[i]);
		
		pastPosition[0] = position;
		MV1SetPosition(afterImageModelHandle[0], pastPosition[0]);
	}
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
		MV1DrawModel(afterImageModelHandle[i]);
	}

	MV1DrawModel(modelHandle);
	
	MV1DrawModel(lingModel);
}