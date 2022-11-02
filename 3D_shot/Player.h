#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Collision.h"


using namespace Math3d;

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
	void Draw();

	Sphere GetCollsionSphere() { return collisionSphere; }

private:
	Player(const Player&);			//コピーコンストラクタ

	Sphere collisionSphere;			//当たり判定球 
};