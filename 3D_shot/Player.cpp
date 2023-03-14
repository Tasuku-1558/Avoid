#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


using namespace Math3d;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() : PlayerBase()
	, pastPosition()
	, emptyModel()
{
	state = State::NOMAL;
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	//プレイヤーモデル読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(modelHandle, SIZE);

	//プレイヤーリングモデル読み込み
	lingModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_LING));
	MV1SetScale(lingModel, LING_SIZE);

	//プレイヤー残像モデル読み込み
	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		emptyModel[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
		MV1SetScale(emptyModel[i], SIZE);
		MV1SetOpacityRate(emptyModel[i], 0.05f);
		MV1SetMaterialEmiColor(emptyModel[i], 0, GetColorF(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

/// <summary>
/// 終了処理
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
/// 活性化処理
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
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	//プレイヤーの位置をセット
	MV1SetPosition(modelHandle, position);

	//リングの位置と回転値をセット
	MV1SetPosition(lingModel, position);
	MV1SetRotationXYZ(lingModel, rotate);

	AfterImage();

	pUpdate(deltaTime);
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime"></param>
void Player::Move(float deltaTime)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	rotate += rotateSpeed * deltaTime;
	
	//上下
	if (CheckHitKey(KEY_INPUT_UP))
	{
		//上方向の移動範囲内なら
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
		//下方向の移動範囲内なら
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
	//左右
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//右方向の移動範囲内なら
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
		//左方向の移動範囲内なら
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
	
	//十字キーの入力があったら
	if (inputFlag)
	{
		// 左右・上下同時押しなどで入力ベクトルが0の時
		if (VSquareSize(inputDirection) < 1.0f)
		{
			return;
		}

		//十字キーの入力方向を正規化
		inputDirection = VNorm(inputDirection);

		//十字キーの移動方向に移動
		position += inputDirection * SPEED * deltaTime;
	}
}

/// <summary>
/// プレイヤーの状態
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
/// 隕石に当たったならば
/// </summary>
/// <param name="deltaTime"></param>
void Player::OnHitMeteorite(float deltaTime)
{
	noDrawFrame = !noDrawFrame;			//2回に1回描画しない
	damageCount += deltaTime;

	//1秒間プレイヤーを点滅させる
	if (damageCount > 1.0f)
	{
		state = State::NOMAL;
		noDrawFrame = false;
		damageCount = 0.0f;
	}
}

/// <summary>
/// プレイヤーの残像処理
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
/// 描画処理
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