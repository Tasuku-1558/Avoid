#include "Meteorite.h"
#include "Player.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"


using namespace Math3d;

/// <summary>
/// コンストラクタ
/// </summary>
Meteorite::Meteorite() : MeteoriteBase()
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
	//モデル読み込み
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
	position = VGet(GetRand(RANDOM_RANGE_X_OR_Y), GetRand(RANDOM_RANGE_X_OR_Y), Z_POSITION);

	dir = DIR;
	random = rand() % RANGE;
	speed = SPEED;

	//ランダムな回転角速度をセット
	rotateSpeed = VGet(GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f);
	rotateAngle = ZERO_VECTOR;
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
	MV1SetRotationXYZ(modelHandle, rotateAngle);

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
		dir = player->GetPosition() - position;

		if (VSize(dir) > 0.1f)
		{
			dir = VNorm(dir);
		}

		popFlag = false;
	}

	//真っすぐ跳ぶ
	else if(random == 1)
	{
		dir = DIR;
	}
	
	position += dir * deltaTime * speed;
	rotateAngle += rotateSpeed;
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