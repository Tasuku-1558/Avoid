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
	void Move(float deltaTime);
	void pUpdate();
	void Damage();
	void Draw();

	Sphere GetCollsionSphere() { return collisionSphere; }

	enum class State state;

private:
	Player(const Player&);			//コピーコンストラクタ

	Sphere collisionSphere;			//当たり判定球 

	int lingModel;
	VECTOR rotate;
	VECTOR rotate_Speed;

	int damageCount;
	bool noDrawFrame;

	static const VECTOR LING_SIZE;
	static const VECTOR LING_ROTATE;
	static const VECTOR LING_ROTATE_SPEED;
	
};