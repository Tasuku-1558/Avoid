#pragma once

#include "Dxlib.h"
#include "MeteoriteBase.h"
#include "Math3D.h"

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
	void RedColor();
	void YellowColor();
	void OrangeCollor();
	void Draw();

private:
	Meteorite(const Meteorite&);				//コピーコンストラクタ

	void Move(float deltaTime, Player* player);		//移動処理

};