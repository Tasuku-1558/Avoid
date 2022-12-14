#include "PlayerBase.h"


const float  PlayerBase::SPEED		 = 400.0f;						//移動速度
const float  PlayerBase::RADIUS		 = 40.0f;						//半径の範囲
const VECTOR PlayerBase::POSITION	 = { 0.0f, 200.0f, 150.0f };	//モデルの位置
const VECTOR PlayerBase::SIZE		 = { 0.4f, 0.4f, 0.4f };		//モデル倍率
const VECTOR PlayerBase::UP			 = { 0, 1, 0 };					//上方向
const VECTOR PlayerBase::DOWN		 = { 0,-1, 0 };					//下方向
const VECTOR PlayerBase::LEFT		 = {-1, 0, 0 };					//左方向
const VECTOR PlayerBase::RIGHT		 = { 1, 0, 0 };					//右方向
const int	 PlayerBase::UP_RANGE	 = 350;							//上方向の移動範囲
const int	 PlayerBase::DOWN_RANGE  = 50;							//下方向の移動範囲
const int	 PlayerBase::LEFT_RANGE  = -410;						//左方向の移動範囲
const int	 PlayerBase::RIGHT_RANGE = 410;							//右方向の移動範囲
const VECTOR PlayerBase::LING_ROTATE	   = { 0.0f, 1.0f, 0.0f };			//リング倍率
const VECTOR PlayerBase::LING_ROTATE_SPEED = { 0.0f, 5.0f, 0.0f };			//リング回転スピード
const VECTOR PlayerBase::LING_SIZE		   = { -0.5f, -0.5f, -0.5f };		//リングサイズ



PlayerBase::PlayerBase()
	: inputDirection()
	, inputFlag(false)
	, lingModel(0)
	, rotate()
	, rotate_Speed()
	, damageCount(0)
	, noDrawFrame(false)
{
	//処理なし
}

PlayerBase::~PlayerBase()
{
	//処理なし
}