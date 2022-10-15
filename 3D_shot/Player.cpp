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
	ModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(ModelHandle, VGet(SIZE, SIZE, SIZE));

	//読み込み失敗でエラー
	if (ModelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [PLAYER]\n");
	}
	
	Dir = VGet(0.0f, 0.0f, 1.0f);
	Position = VGet(0.0f, 100.0f, -20.0f);

	// 当たり判定球を設定
	CollisionSphere.LocalCenter = VGet(0, 0, 0);
	CollisionSphere.WorldCenter = Position;
	CollisionSphere.Radius = RADIUS;
}

//更新処理
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	// mPosition , mDir よりキャラクターの位置・回転をセット
	MV1SetPosition(ModelHandle, Position);

	// 当たり判定の移動
	CollisionSphere.HitTestMove(Position);
}

//移動処理
void Player::Move(float deltaTime)
{
	//上下左右方向
	UP    = { 0, 1, 0 };
	DOWN  = { 0,-1, 0 };
	LEFT  = { -1,0, 0 };
	RIGHT = { 1, 0, 0 };

	InputDirection = ZERO_VECTOR;

	InputFlag = false;

	//上を押していたら上に進む
	if (CheckHitKey(KEY_INPUT_UP))
	{
		InputDirection += UP;
		InputFlag = true;
	}

	//下を押していたら下に進む
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		InputDirection += DOWN;
		InputFlag = true;
	}
	
	//右を押していたら右に進む
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		InputDirection += RIGHT;
		InputFlag = true;
	}

	//左を押していたら左に進む
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		InputDirection += LEFT;
		InputFlag = true;
	}
	
	//十字キーの入力があったら
	if (InputFlag)
	{
		//十字キーの入力方向を正規化する
		InputDirection = VNorm(InputDirection);

		//十字キーの移動方向に移動させる
		Position += InputDirection * SPEED * deltaTime;
	}
}

//描画処理
void Player::Draw()
{
	MV1DrawModel(ModelHandle);

	// 当たり判定デバッグ描画（後で消す）
	DrawSphere3D(CollisionSphere.WorldCenter, CollisionSphere.Radius,
		8, GetColor(0, 255, 0), 0, FALSE);
}