#include "Player.h"
#include "Meteorite.h"
#include "ModelManager.h"
#include "Common.h"
#include <math.h>

using namespace Math3d;

const int Meteorite::RANGE = 2;			//ランダム値の範囲


Meteorite::Meteorite() : MeteoriteBase(ObjectTag::Meteorite)
	, random(0)
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::METEORITE));
	MV1SetScale(modelHandle, VGet(SIZE, SIZE, SIZE));

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [METEORITE]\n");
	}
}

Meteorite::~Meteorite()
{
	//処理なし
}

//初期化処理
void Meteorite::Initialize()
{
	//処理なし
}

//活性化処理
void Meteorite::Activate()
{
	position = VGet(GetRand(RANDOM_RANGE_X_OR_Y), GetRand(RANDOM_RANGE_X_OR_Y), Z_POSITION);
	dir = VGet(0.0f, 0.0f, -1.0f);
	random = rand() % RANGE;

	// ランダムな回転角速度をセット
	rotateSpeed = VGet(GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f);
	rotateAngle = ZERO_VECTOR;

	// 当たり判定球を設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.radius = RADIUS;
	collisionSphere.worldCenter = position;
}

//更新処理
void Meteorite::Update(float deltaTime, Player* player)
{
	Move(deltaTime, player);

	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotateAngle);

	// 当たり判定の移動
	collisionSphere.HitTestMove(position);
}

//移動処理
void Meteorite::Move(float deltaTime, Player* player)
{

	if (popFlag && random == 0)
	{
		dir = player->GetPosition() - position;

		if (VSize(dir) > 0.1f)
		{
			dir = VNorm(dir);
		}
		popFlag = false;
	}
	else if(random == 1)
	{
		dir = VGet(0.0f, 0.0f, -1.0f);
	}
	
	position += dir * deltaTime * SPEED;
	rotateAngle += rotateSpeed;
}

//描画処理
void Meteorite::Draw()
{
	MV1DrawModel(modelHandle);

	// 当たり判定デバッグ描画（後で消す）
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius, 8, GetColor(0, 255, 255), 0, FALSE);
}