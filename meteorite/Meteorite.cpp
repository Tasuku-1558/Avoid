#include "Player.h"
#include "Meteorite.h"
#include "ModelManager.h"
#include <math.h>

using namespace Math3d;


Meteorite::Meteorite() : MeteoriteBase(ObjectTag::Meteorite)
{
	//処理なし
}

Meteorite::~Meteorite()
{
	//処理なし
}

//初期化処理
void Meteorite::Initialize()
{
	ModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::METEORITE));
	MV1SetScale(ModelHandle, VGet(SIZE, SIZE, SIZE));

	//読み込み失敗でエラー
	if (ModelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [METEORITE]\n");
	}

	Position = VGet(/*GetRand(RANDOM_RANGE_X_OR_Y), GetRand(RANDOM_RANGE_X_OR_Y)*/0.0f,100.0f, Z_POSITION);
	Dir = VGet(0.0f, 0.0f, -1.0f);

	// ランダムな回転角速度をセット
	RotateSpeed = VGet(GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f, GetRand(RANDOM_ROTATION_SPEED) / 1000.0f);
	RotateAngle = VGet(0, 0, 0);

	// 当たり判定球を設定
	CollisionSphere.LocalCenter = VGet(0, 0, 0);
	CollisionSphere.Radius = RADIUS;
	CollisionSphere.WorldCenter = Position;
}

//更新処理
void Meteorite::Update(float deltaTime, Player* player)
{
	Move(deltaTime, player);

	MV1SetPosition(ModelHandle, Position);
	MV1SetRotationXYZ(ModelHandle, RotateAngle);

	// 当たり判定の移動
	CollisionSphere.HitTestMove(Position);
}

//移動処理
void Meteorite::Move(float deltaTime, Player* player)
{
	
	/*if (PopFlag)
	{
		Dir = player->GetPosition() - Position;

		if (VSize(Dir) > 0.1f)
		{
			Dir = VNorm(Dir);
		}
		PopFlag = false;
	}*/
	/*else if()
	{
		Dir = VGet(10.0f,10.0f,0.0f);
		if (VSize(Dir) > 0.1f)
		{
			Dir = VNorm(Dir);
		}
	}*/
	
	
	Position += Dir * deltaTime * SPEED;
	RotateAngle += RotateSpeed;
}

//描画処理
void Meteorite::Draw()
{
	MV1DrawModel(ModelHandle);

	// 当たり判定デバッグ描画（後で消す）
	DrawSphere3D(CollisionSphere.WorldCenter, CollisionSphere.Radius, 8, GetColor(0, 255, 255), 0, FALSE);
}

//隕石出現カウント
//void Meteorite::MeteoritePopCount(float deltaTime)
// {
//	PopCount += deltaTime;
//
//	if (PopCount > 1.0)
//	{
//		PopCount = 0.0f;
//	}
//}