#pragma once

#include "ObjectBase.h"

//Playerの親クラス
//ObjectBaseを継承


class PlayerBase : public ObjectBase
{
public:
			 PlayerBase(ObjectTag tag);
	virtual ~PlayerBase();



protected:
	ObjectTag Tag;					//オブジェクト種類
	VECTOR inputDirection;			//入力された方向
	VECTOR UP;						//上方向
	VECTOR DOWN;					//下方向
	VECTOR LEFT;					//左方向
	VECTOR RIGHT;					//右方向
	bool inputFlag;					//キー入力フラグ


	//静的定数
	static const float SIZE;		//モデル倍率
	static const float SPEED;		//移動速度
	static const float RADIUS;		//半径の範囲

};