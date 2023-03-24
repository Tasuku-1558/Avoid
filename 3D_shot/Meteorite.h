#pragma once

#include "MeteoriteBase.h"
#include "Math3D.h"

class Player;

/// <summary>
/// 隕石クラス
/// </summary>
class Meteorite final : public MeteoriteBase
{
public:
	Meteorite();
	virtual ~Meteorite();

	void Update(float deltaTime, Player* player);		//更新処理
	void Draw();										//描画処理

	void SpeedUp();														//隕石のスピード変化
	void ChangeColor(float red, float green, float blue);				//各Waveでの隕石の色変更

private:
	Meteorite(const Meteorite&);					//コピーコンストラクタ

	void Initialize();								//初期化処理
	void Activate();								//活性化処理
	void Move(float deltaTime, Player* player);		//移動処理
	void Finalize();								//終了処理

};