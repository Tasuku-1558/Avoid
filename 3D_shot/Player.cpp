#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	: playerState(PlayerState::NOMAL)
{
	Initialize();
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
	//プレイヤーモデルの読み込みとサイズの設定
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(modelHandle, SIZE);
	position = POSITION;

	//プレイヤーリングモデルの読み込みとサイズの設定
	lingModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_LING));
	MV1SetScale(lingModel, LING_SIZE);
	rotateSpeed = LING_ROTATE_SPEED;

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		//プレイヤー残像モデルの読み込みとサイズの設定
		afterImageModelHandle[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
		MV1SetScale(afterImageModelHandle[i], SIZE);

		//モデルの不透明度の設定
		//0.0fに近いほど透明度が上がる
		MV1SetOpacityRate(afterImageModelHandle[i], OPACITY);

		//モデルのエミッシブカラーを変更
		MV1SetMaterialEmiColor(afterImageModelHandle[i], MATERIAL_INDEX, AFTER_IMAGE_COLOR);

		pastPosition[i] = POSITION;
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
		MV1DeleteModel(afterImageModelHandle[i]);
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	AfterImage();

	HitMeteorite(deltaTime);
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Player::Move(float deltaTime)
{
	//入力方向を初期化する
	inputDirection = ZERO_VECTOR;

	//リングを回転
	rotate += rotateSpeed * deltaTime;

	//プレイヤーリングモデルの位置と回転値を設定
	MV1SetPosition(lingModel, position);
	MV1SetRotationXYZ(lingModel, rotate);
	
	KeyInput();
	
	//十字キーの入力があったら
	if (inputFlag)
	{
		// 左右・上下同時押しなどで入力ベクトルが1.0以下の時
		if (VSquareSize(inputDirection) < MAX_INPUT_DIRECTION)
		{
			return;
		}

		//十字キーの入力方向を正規化
		direction = VNorm(inputDirection);

		//十字キーの移動方向に移動
		position += direction * SPEED * deltaTime;
	}

	//プレイヤーモデルの位置を設定
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// キー入力処理
/// </summary>
void Player::KeyInput()
{
	Key key[] =
	{
		{KEY_INPUT_UP,	  position.y, UP_RANGE,	   UP},
		{KEY_INPUT_RIGHT, position.x, RIGHT_RANGE, RIGHT},
	};

	Key key2[] =
	{
		{KEY_INPUT_DOWN, position.y, DOWN_RANGE, DOWN},
		{KEY_INPUT_LEFT, position.x, LEFT_RANGE, LEFT},
	};

	for (int i = 0; i < 2; i++)
	{
		if (CheckHitKey(key[i].input))
		{
			if (key[i].position < key[i].range)
			{
				inputDirection += key[i].dir;
				inputFlag = true;
			}
			else
			{
				inputDirection = ZERO_VECTOR;
			}
		}
		if (CheckHitKey(key2[i].input))
		{
			if (key2[i].position > key2[i].range)
			{
				inputDirection += key2[i].dir;
				inputFlag = true;
			}
			else
			{
				inputDirection = ZERO_VECTOR;
			}
		}
	}
}

/// <summary>
/// 隕石に衝突した
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Player::HitMeteorite(float deltaTime)
{
	//プレイヤーの状態が被弾状態なら
	if (playerState == PlayerState::DAMAGE)
	{
		//2回に1回描画しない
		noDrawFrame = !noDrawFrame;

		//ダメージカウントを開始する
		damageTime += deltaTime;

		//1秒間プレイヤーを点滅させる
		if (damageTime > MAX_DAMAGE_TIME)
		{
			//通常状態へ戻す
			playerState = PlayerState::NOMAL;

			noDrawFrame = false;
			damageTime = INITIAL_DAMAGE_TIME;
		}
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
		MV1SetPosition(afterImageModelHandle[i], pastPosition[i]);
		
		pastPosition[0] = position;
		MV1SetPosition(afterImageModelHandle[0], pastPosition[0]);
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
		MV1DrawModel(afterImageModelHandle[i]);
	}

	MV1DrawModel(modelHandle);
	
	MV1DrawModel(lingModel);
}