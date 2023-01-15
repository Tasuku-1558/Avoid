#pragma once

#include "Dxlib.h"
#include "MeteoriteBase.h"
#include "Math3D.h"

class Player;

using namespace Math3d;


/// <summary>
/// 隕石クラス
/// MeteoriteBaseクラスを継承
/// </summary>
class Meteorite final : public MeteoriteBase
{
public:
	 Meteorite();
	~Meteorite();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void SpeedUp();					//隕石スピードアップ
	void ChangeColor(float red, float green, float blue);				//各Waveでの隕石の色変更
	void Draw();

private:
	Meteorite(const Meteorite&);				//コピーコンストラクタ

	void Move(float deltaTime, Player* player);		//移動処理

};