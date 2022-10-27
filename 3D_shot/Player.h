#pragma once

#include "DxLib.h"
#include "Math3D.h"
#include "Collision.h"
#include "PlayerBase.h"

//Playerの状態
enum class State
{
	Nomal,
	Miss,
};

//PlayerBaseクラスを継承
class Player final : public PlayerBase
{
public:
	 Player();    //コンストラクタ
	~Player();    //デストラクタ

	void Initialize();
	void Activate();
	void Update(float deltaTime);
	void Pstate(float deltaTime);
	void Move(float deltaTime);
	void Damege(float deltaTime);
	void Draw() override;

	Math3d::Sphere GetCollsionSphere() { return collisionSphere; }
	enum class State state;
private:
	Player(const Player&);			//コピーコンストラクタ

	bool noDrawFrame;				//描画しないフレームか
	int damegeCount;

	Math3d::Sphere collisionSphere;	//当たり判定球 
};