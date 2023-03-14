#pragma once

#include "Dxlib.h"
#include "MeteoriteBase.h"
#include "Math3D.h"

class Player;

/// <summary>
/// 隕石クラス
/// MeteoriteBaseクラスを継承
/// </summary>
class Meteorite final : public MeteoriteBase
{
public:
	Meteorite();
	virtual ~Meteorite();

	void Initialize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void SpeedUp();														//隕石のスピード変化
	void ChangeColor(float red, float green, float blue);				//各Waveでの隕石の色変更
	void Draw();

private:
	Meteorite(const Meteorite&);					//コピーコンストラクタ

	void Move(float deltaTime, Player* player);		//移動処理
	void Finalize();

};