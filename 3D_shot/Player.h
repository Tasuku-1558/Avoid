#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"

/// <summary>
/// プレイヤークラス
/// PlayerBaseクラスを継承
/// </summary>
class Player final : public PlayerBase
{
public:
	Player();
	virtual ~Player();

	void Update(float deltaTime);
	void Draw();

	//プレイヤーの状態
	enum class PlayerState
	{
		NOMAL,		//通常状態
		DAMAGE,		//被弾状態
	};

	PlayerState playerState;	//プレイヤーの状態

private:
	Player(const Player&);			//コピーコンストラクタ

	void Initialize();
	void Activate();
	void Move(float deltaTime);					//移動処理
	void pUpdate(float deltaTime);				//プレイヤーの状態
	void OnHitMeteorite(float deltaTime);		//隕石に当たったならば
	void AfterImage();							//プレイヤーの残像処理
	void Finalize();							//終了処理


	int emptyModel[3];			//残像モデル格納用
	VECTOR pastPosition[3];		//プレイヤーの過去の位置
};