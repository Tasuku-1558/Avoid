#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Collision.h"


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

	Sphere GetCollsionSphere() { return collisionSphere; }

	enum class State state;

private:
	Player(const Player&);			//コピーコンストラクタ

	void Move(float deltaTime);		//移動処理
	void pUpdate();					//状態変化
	void OnHitMeteorite();			//隕石に当たった

	Sphere collisionSphere;			//当たり判定球 

	int lingModel;
	VECTOR rotate;
	VECTOR rotate_Speed;

	int damageCount;
	bool noDrawFrame;

	static const VECTOR LING_SIZE;				//リング倍率
	static const VECTOR LING_ROTATE;			//リング回転角度
	static const VECTOR LING_ROTATE_SPEED;		//リング回転スピード
	
};