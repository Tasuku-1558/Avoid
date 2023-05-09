#pragma once

#include "PlayerBase.h"
#include "Math3D.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player final : public PlayerBase
{
public:
	Player();
	virtual ~Player();

	void Update(float deltaTime);		//更新処理
	void Draw();						//描画処理

	//プレイヤーの状態
	enum class PlayerState
	{
		NOMAL,		//通常状態
		DAMAGE,		//被弾状態
	};

	struct Key
	{
		int input;	//キー操作
		float position;
		int range;
		VECTOR dir;	//方向
	};

	PlayerState playerState;	//プレイヤーの状態

private:
	Player(const Player&);		//コピーコンストラクタ

	void Initialize();						//初期化処理
	void Move(float deltaTime);				//移動処理
	void KeyInput();						//キー入力処理
	void HitMeteorite(float deltaTime);		//隕石に衝突した
	void AfterImage();						//プレイヤーの残像処理
	void Finalize();						//終了処理
};