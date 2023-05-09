#include "Meteorite.h"
#include "ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="inPlayerPosition">プレイヤーの座標</param>
Meteorite::Meteorite(VECTOR inPlayerPosition)
{
	Initialize();

	playerPosition = inPlayerPosition;
}

/// <summary>
/// デストラクタ
/// </summary>
Meteorite::~Meteorite()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Meteorite::Initialize()
{
	//隕石モデルの読み込みとサイズの設定
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::METEORITE));
	MV1SetScale(modelHandle, SIZE);

	//隕石の位置をランダム値に
	position = RANDOM_POSITION;

	//隕石が進む方向にランダム値を入れる
	randomDirection = rand() % RANGE_DIRECTION;

	speed = SPEED;

	//ランダムな回転速度を設定
	rotateSpeed = RANDOM_ROTATE_SPEED;
}

/// <summary>
/// 終了処理
/// </summary>
void Meteorite::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Meteorite::Update(float deltaTime)
{
	Move(deltaTime);
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Meteorite::Move(float deltaTime)
{
	//ランダム値が0で出現フラグがtrueなら
	//プレイヤーに向かって跳ぶ
	if (popFlag && randomDirection == TRACKING_VALUE)
	{
		//プレイヤーから隕石の座標を引いた値を取得
		direction = playerPosition - position;

		popFlag = false;
	}

	//ランダム値が1なら
	//真っすぐ跳ぶ
	else if(randomDirection == STRAIGHT_VALUE)
	{
		direction = DIRECTION;
	}

	//ベクトルの正規化
	direction = VNorm(direction);
	
	position += direction * speed * deltaTime;
	rotate += rotateSpeed;

	//隕石の位置と回転値をセット
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotate);
}

/// <summary>
/// 隕石のスピード変化
/// </summary>
void Meteorite::SpeedUp()
{
	speed = SPEED_UP;
}

/// <summary>
/// 描画処理
/// </summary>
void Meteorite::Draw()
{
	MV1DrawModel(modelHandle);
}