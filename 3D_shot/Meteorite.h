#pragma once

#include "Dxlib.h"
#include "MeteoriteBase.h"
#include "Math3D.h"
#include "Collision.h"


class Player;

using namespace Math3d;

//่ฆฮNX
//MeteoriteBaseNX๐pณ
class Meteorite final : public MeteoriteBase
{
public:
	 Meteorite();
	~Meteorite();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void Draw();
	
	Sphere GetCollisionSphere() { return collisionSphere; } //ฝ่ป่๐ิท

private:
	Meteorite(const Meteorite&);				//Rs[RXgN^

	void Move(float deltaTime, Player* player);		//ฺฎ

	int shadowImage;					//่ฆฮe
	VECTOR shadowPosition;
	Sphere collisionSphere;				//ฝ่ป่

};