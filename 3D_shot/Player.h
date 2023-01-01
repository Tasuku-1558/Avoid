#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"


using namespace Math3d;

/// <summary>
/// プレイヤーの状態
/// </summary>
enum class State
{
	NOMAL,
	DAMAGE,
};


/// <summary>
/// プレイヤークラス
/// PlayerBaseクラスを継承
/// </summary>
class Player final : public PlayerBase
{
public:
	 Player();    //コンストラクタ
	~Player();    //デストラクタ

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	enum class State state;

private:
	Player(const Player&);			//コピーコンストラクタ

	void Move(float deltaTime);		//移動処理
	void pUpdate();					//プレイヤーの状態
	void OnHitMeteorite();			//隕石に当たったならば

};