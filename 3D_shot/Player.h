#pragma once

#include "DxLib.h"
#include "math3D.h"
#include "Collision.h"
#include "PlayerBase.h"


//PlayerBaseクラスを継承
class Player final : public PlayerBase
{
public:
	Player();    //コンストラクタ
	~Player();   //デストラクタ

	void Initialize();
	void Update(float deltaTime);
	void Move(float deltaTime);
	void Draw() override;

	Math3d::Sphere GetCollsionSphere() { return CollisionSphere; }
	
private:
	Player(const Player&);			//コピーコンストラクタ

	
	Math3d::Sphere CollisionSphere;	//当たり判定球 
};