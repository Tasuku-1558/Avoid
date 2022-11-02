#pragma once

#include "ObjectBase.h"

//Playerの親クラス
//ObjectBaseを継承

class PlayerBase : public ObjectBase
{
public:
			 PlayerBase();
	virtual ~PlayerBase();

protected:
	VECTOR inputDirection;			//入力された方向
	bool   inputFlag;				//キー入力フラグ


	//静的定数
	static const float SPEED;		//移動速度
	static const float RADIUS;		//半径の範囲
	static const VECTOR POSITION;	//モデルの位置
	static const VECTOR SIZE;		//モデル倍率
	static const VECTOR UP;			//上方向
	static const VECTOR DOWN;		//下方向
	static const VECTOR LEFT;		//左方向
	static const VECTOR RIGHT;		//右方向

};