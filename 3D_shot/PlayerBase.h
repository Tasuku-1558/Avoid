#pragma once

#include "ObjectBase.h"

/// <summary>
/// Playerの親クラス
/// ObjectBaseを継承
/// </summary>
class PlayerBase : public ObjectBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

protected:

	int    lingModel;				//リングモデル格納用
	float  damageCount;				//ダメージ時間カウント
	bool   inputFlag;				//キー入力フラグ
	bool   noDrawFrame;				//モデルを2回に１回は描画しない
	VECTOR inputDirection;			//入力された方向
	VECTOR rotate;					//リング回転
	VECTOR rotateSpeed;				//リング回転スピード


	//定数
	static const float SPEED;		//移動速度
	const float	  OPACITY;			//不透明度
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
	static const int AFTER_IMAGE_NUMBER;	//プレイヤーの残像枚数
	const COLOR_F AFTER_IMAGE_COLOR;			//残像モデルのエミッシブカラー


	static const VECTOR LING_SIZE;				//リング倍率
	static const VECTOR LING_ROTATE_SPEED;		//リング回転スピード

};