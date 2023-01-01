#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"

using namespace Math3d;


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() : PlayerBase()
{
	state = State::NOMAL;
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL || lingModel != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(modelHandle, SIZE);
	
	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [PLAYER]\n");
	}

	lingModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_LING));
	MV1SetScale(lingModel, LING_SIZE);

	if (lingModel < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [PLAYER_LING]\n");
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(lingModel);
	lingModel = NULL;
}

/// <summary>
/// 活性化処理
/// </summary>
void Player::Activate()
{
	position = POSITION;

	rotate = LING_ROTATE;
	rotate_Speed = LING_ROTATE_SPEED;

	noDrawFrame = false;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	// プレイヤーの位置をセット
	MV1SetPosition(modelHandle, position);

	MV1SetPosition(lingModel, position);
	MV1SetRotationXYZ(lingModel, rotate);
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime"></param>
void Player::Move(float deltaTime)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	rotate += rotate_Speed * deltaTime;
	
	//上下
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
	//左右
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
/// 隕石に当たったならば
/// </summary>
void Player::OnHitMeteorite()
{
	noDrawFrame = !noDrawFrame;			//2回に1回描画しない
	damageCount += 1;

	if (damageCount > 10)
	{
		state = State::NOMAL;
		noDrawFrame = false;
		damageCount = 0;
	}
}

/// <summary>
/// 描画処理
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