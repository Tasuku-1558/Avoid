#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 400.0f;						//移動速度
const float  PlayerBase::RADIUS   = 40.0f;						//半径の範囲
const VECTOR PlayerBase::POSITION = { 0.0f, 200.0f, 150.0f };	//モデルの位置
const VECTOR PlayerBase::SIZE	  = { 0.4f, 0.4f, 0.4f };		//モデル倍率
const VECTOR PlayerBase::UP		  = { 0, 1, 0 };				//上方向
const VECTOR PlayerBase::DOWN	  = { 0,-1, 0 };				//下方向
const VECTOR PlayerBase::LEFT	  = {-1, 0, 0 };				//左方向
const VECTOR PlayerBase::RIGHT	  = { 1, 0, 0 };				//右方向


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
