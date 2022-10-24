#pragma once

#include "Dxlib.h"
#include "Math3D.h"
#include "Collision.h"
#include "MeteoriteBase.h"

class Player;


//MeteoriteBaseクラスを継承
class Meteorite final : public MeteoriteBase
{
public:
	 Meteorite();
	~Meteorite();

	void Initialize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void Move(float deltaTime, Player* player);
	void Draw();
	
	
	Math3d::Sphere GetCollisionSphere() { return collisionSphere; } //当たり判定球を返す

private:
	Meteorite(const Meteorite&);				//コピーコンストラクタ

	Math3d::Sphere collisionSphere;				//当たり判定球

	int random;									//隕石のランダム値
	
	//静的定数
	static const int RANGE;						//ランダム値の範囲

};