#include "Meteorite.h"
#include "Player.h"
#include "ModelManager.h"
#include "Common.h"
#include <math.h>

using namespace Math3d;

Meteorite::Meteorite() : MeteoriteBase()
	, shadowImage(0)
{
	//処理なし
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

	shadowImage = LoadGraph("data/image/shadow.png");
}

//終了処理
void Meteorite::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(shadowImage);
	shadowImage = NULL;
}

//活性化処理
void Meteorite::Activate()
{
	position = VGet(GetRand(RANDOM_RANGE_X_OR_Y), GetRand(RANDOM_RANGE_X_OR_Y), Z_POSITION);
	dir = DIR;
	random = rand() % RANGE;

	// ランダムな回転角速度をセット
	rotateSpeed = VGet(GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f);
	rotateAngle = ZERO_VECTOR;

	// 当たり判定球を設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius		= RADIUS;
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
	
	position += dir * deltaTime * SPEED;
	rotateAngle += rotateSpeed;
}

//描画処理
void Meteorite::Draw()
{
	MV1DrawModel(modelHandle);
	
	DrawBillboard3D(VGet(position.x, 2.0f, position.z), 0.5f, 0.5f, 250.0f, 0.0f, shadowImage, TRUE);
}