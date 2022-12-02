#pragma once

#include "Dxlib.h"
#include "MeteoriteBase.h"
#include "Math3D.h"
#include "Collision.h"


class Player;

using namespace Math3d;

//隕石クラス
//MeteoriteBaseクラスを継承
class Meteorite final : public MeteoriteBase
{
public:
	 Meteorite();
	~Meteorite();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void SpeedUp();
	void Draw();
	
	Sphere GetCollisionSphere() { return collisionSphere; } //当たり判定球を返す


private:
	Meteorite(const Meteorite&);				//コピーコンストラクタ

	void Move(float deltaTime, Player* player);					//移動処理
	
	int shadowMapHandle;
	
	Sphere collisionSphere;				//当たり判定球

};