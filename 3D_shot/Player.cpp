#include "Player.h"
#include "Common.h"
#include "ModelManager.h"

using namespace Math3d;

const VECTOR Player::LING_ROTATE	   = { 0.0f, 1.0f, 0.0f };		//リング倍率
const VECTOR Player::LING_ROTATE_SPEED = { 0.0f, 5.0f, 0.0f };		//リング回転角度
const VECTOR Player::LING_SIZE		   = { -0.5f, -0.5f, -0.5f };	//リング回転スピード

//コンストラクタ
Player::Player() : PlayerBase()
	, lingModel(0)
	, rotate()
	, rotate_Speed()
	, damageCount(0)
	, noDrawFrame(false)
{
	state = State::Nomal;
}

//デストラクタ
Player::~Player()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL || lingModel != NULL)
	{
		Finalize();
	}
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

	lingModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_LING));
	MV1SetScale(lingModel, LING_SIZE);

	if (lingModel < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [PLAYER_LING]\n");
	}
}

//終了処理
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(lingModel);
	lingModel = NULL;
}

//活性化処理
void Player::Activate()
{
	position = POSITION;

	// 当たり判定球を設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius		= RADIUS;

	rotate = LING_ROTATE;
	rotate_Speed = LING_ROTATE_SPEED;

	noDrawFrame = false;
}

//更新処理
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	// プレイヤーの位置をセット
	MV1SetPosition(modelHandle, position);

	// 当たり判定の移動
	collisionSphere.HitTestMove(position);

	MV1SetPosition(lingModel, position);
	MV1SetRotationXYZ(lingModel, rotate);
	
}

//移動処理
void Player::Move(float deltaTime)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	rotate += rotate_Speed * deltaTime;
	
	//上下
	if (CheckHitKey(KEY_INPUT_UP))
	{
		if (position.y < 350)
		{
			inputDirection.y += 1.0f;
			inputFlag = true;
		}
		else
		{
			inputDirection.y = 0.0f;
		}
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (position.y > 50)
		{
			inputDirection.y -= 1.0f;
			inputFlag = true;
		}
		else
		{
			inputDirection.y = 0.0f;
		}
	}
	//左右
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		if (position.x < 410)
		{
			inputDirection.x += 1.0f;
			inputFlag = true;
		}
		else
		{
			inputDirection.x = 0.0f;
		}
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		if (position.x > -410)
		{
			inputDirection.x -= 1.0f;
			inputFlag = true;
		}
		else
		{
			inputDirection.x = 0.0f;
		}
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

void Player::pUpdate()
{
	switch (state)
	{
	case State::Nomal:
		break;

	case State::Damage:
		OnHitMeteorite();
		break;
	}
}

//隕石に当たった
void Player::OnHitMeteorite()
{
	noDrawFrame = !noDrawFrame;			//2回に1回描画しない
	damageCount += 1;

	if (damageCount > 10)
	{
		state = State::Nomal;
		noDrawFrame = false;
		damageCount = 0;
	}
}

//描画処理
void Player::Draw()
{
	pUpdate();

	if (noDrawFrame == true)
	{
		return;
	}

	MV1DrawModel(modelHandle);
	
	MV1DrawModel(lingModel);
}