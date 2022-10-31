#include "Player.h"
#include "Common.h"
#include "ModelManager.h"

using namespace Math3d;

//コンストラクタ
Player::Player() : PlayerBase(ObjectTag::Player)
{
	//処理なし
}

//デストラクタ
Player::~Player()
{
	//処理なし
}

//初期化処理
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(modelHandle, SIZE);
	
	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [PLAYER]\n");
	}
}

//活性化処理
void Player::Activate()
{
	position = POSITION;

	// 当たり判定球を設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius		= RADIUS;
}

//更新処理
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	// プレイヤーの位置をセット
	MV1SetPosition(modelHandle, position);

	// 当たり判定の移動
	collisionSphere.HitTestMove(position);
}

//移動処理
void Player::Move(float deltaTime)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;
	
	//上キーを押したら
	if (CheckHitKey(KEY_INPUT_UP))
	{
		inputDirection += UP;
		inputFlag = true;
	}

	//下キーを押したら
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		inputDirection += DOWN;
		inputFlag = true;
	}

	//右キーを押したら
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		inputDirection += RIGHT;
		inputFlag = true;
	}

	//左キーを押したら
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		inputDirection += LEFT;
		inputFlag = true;
	}
	
	//十字キーの入力があったら
	if (inputFlag)
	{
		//十字キーの入力方向を正規化
		inputDirection = VNorm(inputDirection);

		//十字キーの移動方向に移動
		position += inputDirection * SPEED * deltaTime;
	}
}

//描画処理
void Player::Draw()
{
	MV1DrawModel(modelHandle);

	// 当たり判定デバッグ用描画
	//DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius, 8, GetColor(0, 255, 0), 0, FALSE);
}