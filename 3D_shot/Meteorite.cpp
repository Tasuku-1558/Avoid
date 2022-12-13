#include "Meteorite.h"
#include "Player.h"
#include "ModelManager.h"
#include "Common.h"
#include <math.h>

using namespace Math3d;

Meteorite::Meteorite() : MeteoriteBase()
{
	Initialize();
	Activate();
}

Meteorite::~Meteorite()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

//初期化処理
void Meteorite::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::METEORITE));
	MV1SetScale(modelHandle, SIZE);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [METEORITE]\n");
	}
}

//終了処理
void Meteorite::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

//活性化処理
void Meteorite::Activate()
{
	position = VGet(GetRand(RANDOM_RANGE_X_OR_Y), GetRand(RANDOM_RANGE_X_OR_Y), Z_POSITION);
	dir = DIR;
	random = rand() % RANGE;
	speed = SPEED;

	// ランダムな回転角速度をセット
	rotateSpeed = VGet(GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f);
	rotateAngle = ZERO_VECTOR;
}

//更新処理
void Meteorite::Update(float deltaTime, Player* player)
{
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotateAngle);

	Move(deltaTime, player);
}

//移動処理
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

void Meteorite::RedColor()
{
	MV1SetDifColorScale(modelHandle, GetColorF(5.0f, 0.0f, 0.0f, 1.0f));
}

void Meteorite::YellowColor()
{
	MV1SetDifColorScale(modelHandle, GetColorF(50.0f, 50.0f, 0.0f, 1.0f));
}

void Meteorite::OrangeCollor()
{
	MV1SetDifColorScale(modelHandle, GetColorF(0.0f, 1.0f, 1.0f, 1.0f));
}

void Meteorite::SpeedUp()
{
	speed = SPEED_UP;
}

//描画処理
void Meteorite::Draw()
{
	MV1DrawModel(modelHandle);
}