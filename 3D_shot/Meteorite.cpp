#include "Meteorite.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "ModelManager.h"


using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
Meteorite::Meteorite()
{
	Initialize();
	Activate();
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
}

/// <summary>
/// 終了処理
/// </summary>
void Meteorite::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 活性化処理
/// </summary>
void Meteorite::Activate()
{
	//隕石の位置にランダム値を入れる
	position = VGet((float)GetRand(400), (float)GetRand(400), POSITION_Z);

	random = rand() % RANGE;
	speed = SPEED;

	//ランダムな回転速度を設定
	rotateSpeed = VGet(GetRandf(0.0f, MAX_ROTATE), GetRandf(0.0f, MAX_ROTATE), GetRandf(0.0f, MAX_ROTATE));
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void Meteorite::Update(float deltaTime, Player* player)
{
	//隕石の位置と回転値をセット
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotate);

	Move(deltaTime, player);
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void Meteorite::Move(float deltaTime, Player* player)
{
	//プレイヤーに向かって跳ぶ
	if (popFlag && random == 0)
	{
		direction = player->GetPosition() - position;

		if (VSize(direction) > 0.1f)
		{
			direction = VNorm(direction);
		}

		popFlag = false;
	}

	//真っすぐ跳ぶ
	else if(random == 1)
	{
		direction = DIRECTION;
	}
	
	position += direction * deltaTime * speed;
	rotate += rotateSpeed;
}

/// <summary>
/// 各Waveでの隕石の色変更
/// </summary>
void Meteorite::ChangeColor(float red, float green, float blue)
{
	MV1SetDifColorScale(modelHandle, GetColorF(red, green, blue, 1.0f));
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