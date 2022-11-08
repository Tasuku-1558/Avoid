#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 400.0f;						//移動速度
const float  PlayerBase::RADIUS   = 40.0f;						//半径の範囲
const VECTOR PlayerBase::POSITION = VGet(0.0f, 200.0f, 80.0f); //モデルの位置
const VECTOR PlayerBase::SIZE     = VGet(0.4f, 0.4f, 0.4f);		//モデル倍率

PlayerBase::PlayerBase()
	: inputDirection()
	, inputFlag(false)
{
	//処理なし
}

PlayerBase::~PlayerBase()
{
	//処理なし
}
