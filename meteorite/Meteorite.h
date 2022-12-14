#pragma once

#include "Dxlib.h"
#include "math3D.h"
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
	void Update(float deltaTime, Player* player);
	void Move(float deltaTime, Player* player);
	void Draw() override;
	//void MeteoritePopCount(float deltaTime);
	//float GetMeteoriteCount() { return PopCount; }

	Math3d::Sphere GetCollisionSphere() { return CollisionSphere; } //当たり判定球を返す

	

private:
	Meteorite(const Meteorite&);				//コピーコンストラクタ
	

	Math3d::Sphere CollisionSphere;				//当たり判定球

};