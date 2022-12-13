#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"


using namespace Math3d;

enum class State
{
	Nomal,
	Damage,
};

//プレイヤークラス
//PlayerBaseクラスを継承
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
	void pUpdate();					//状態変化
	void OnHitMeteorite();			//隕石に当たった

};