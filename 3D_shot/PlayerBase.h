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
	int    lingModel;				//リングモデル格納用
	VECTOR rotate;					//リング回転
	VECTOR rotate_Speed;			//リング回転スピード
	int    damageCount;				//ダメージ時間カウント
	bool   noDrawFrame;				//モデルを2回に１回は描画しない



	//静的定数
	static const float SPEED;		//移動速度
	static const float RADIUS;		//半径の範囲
	static const VECTOR POSITION;	//モデルの位置
	static const VECTOR SIZE;		//モデル倍率
	static const VECTOR UP;			//上方向
	static const VECTOR DOWN;		//下方向
	static const VECTOR LEFT;		//左方向
	static const VECTOR RIGHT;		//右方向
	static const int	UP_RANGE;	//上方向の移動範囲
	static const int    DOWN_RANGE; //下方向の移動範囲
	static const int    LEFT_RANGE; //左方向の移動範囲
	static const int    RIGHT_RANGE;//右方向の移動範囲
	static const VECTOR LING_SIZE;				//リング倍率
	static const VECTOR LING_ROTATE;			//リング回転スピード
	static const VECTOR LING_ROTATE_SPEED;		//リングサイズ

};