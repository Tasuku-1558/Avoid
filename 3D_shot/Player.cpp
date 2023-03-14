#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	: PlayerBase()
	, pastPosition()
	, emptyModel()
	, playerState(PlayerState::NOMAL)
{
	Initialize();
	Activate();
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
	//プレイヤーモデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(modelHandle, SIZE);

	//プレイヤーリングモデルの読み込み
	lingModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_LING));
	MV1SetScale(lingModel, LING_SIZE);

	//残像の枚数分読み込む
	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		//プレイヤー残像モデルの読み込みとサイズの設定
		emptyModel[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
		MV1SetScale(emptyModel[i], SIZE);

		//モデルの不透明度の設定
		//0.0fに近いほど透明度が上がる
		MV1SetOpacityRate(emptyModel[i], OPACITY);

		//モデルのエミッシブカラーを変更
		MV1SetMaterialEmiColor(emptyModel[i], 0, AFTER_IMAGE_COLOR);
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

	rotateSpeed = LING_ROTATE_SPEED;

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		pastPosition[i] = POSITION;
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
	//入力方向を初期化する
	inputDirection = ZERO_VECTOR;

	rotate += rotateSpeed * deltaTime;
	
	//上下移動
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
	//左右移動
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
		direction = VNorm(inputDirection);

		//十字キーの移動方向に移動
		position += direction * SPEED * deltaTime;
	}
}

/// <summary>
/// プレイヤーの状態
/// </summary>
/// <param name="deltaTime"></param>
void Player::pUpdate(float deltaTime)
{
	switch (playerState)
	{
	case PlayerState::NOMAL:
		break;

	case PlayerState::DAMAGE:
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

	//ダメージカウントを開始する
	damageCount += deltaTime;

	//1秒間プレイヤーを点滅させる
	if (damageCount > 1.0f)
	{
		playerState = PlayerState::NOMAL;
		noDrawFrame = false;
		damageCount = 0.0f;
	}
}

/// <summary>
/// プレイヤーの残像処理
/// </summary>
void Player::AfterImage()
{
	for (int i = AFTER_IMAGE_NUMBER - 1; i >= 1; i--)
	{
		pastPosition[i] = pastPosition[i - 1];
		MV1SetPosition(emptyModel[i], pastPosition[i]);

		pastPosition[0] = position;
		MV1SetPosition(emptyModel[0], pastPosition[0]);
	}
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