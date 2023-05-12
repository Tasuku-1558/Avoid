#pragma once

#include "ObjectBase.h"

/// <summary>
/// プレイヤー基底クラス
/// </summary>
class PlayerBase : public ObjectBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

protected:

	int    lingModel;					//リングモデル格納用
	int	   afterImageModelHandle[10];	//残像モデル格納用
	float  damageTime;					//ダメージ時間カウント
	bool   inputFlag;					//キー入力フラグ
	bool   noDrawFrame;					//モデルを2回に１回は描画しない
	VECTOR inputDirection;				//入力された方向
	VECTOR rotate;						//リング回転
	VECTOR rotateSpeed;					//リング回転スピード
	VECTOR pastPosition[10];			//プレイヤーの過去の位置

	//定数
	const int	  KEY_INPUT_PATTERN;	//キー入力パターン
	const int	  UP_RANGE;				//上方向の移動範囲
	const int     DOWN_RANGE;			//下方向の移動範囲
	const int     LEFT_RANGE;			//左方向の移動範囲
	const int     RIGHT_RANGE;			//右方向の移動範囲
	const int	  AFTER_IMAGE_NUMBER;	//プレイヤーの残像枚数
	const int	  MATERIAL_INDEX;		//エミッシブカラーを変更するマテリアルの番号

	const float   SPEED;				//移動速度
	const float	  OPACITY;				//不透明度
	const float   RADIUS;				//半径の範囲
	const float   MAX_DAMAGE_TIME;		//最大点滅時間
	const float	  INITIAL_DAMAGE_TIME;	//初期のダメージ時間
	const float	  MAX_INPUT_DIRECTION;	//最大入力ベクトル

	const VECTOR  INITIAL_POSITION;		//初期のプレイヤーの位置
	const VECTOR  SIZE;					//倍率
	const VECTOR  UP;					//上方向
	const VECTOR  DOWN;					//下方向
	const VECTOR  LEFT;					//左方向
	const VECTOR  RIGHT;				//右方向
	const VECTOR  LING_SIZE;			//リング倍率
	const VECTOR  LING_ROTATE_SPEED;	//リング回転スピード

	const COLOR_F AFTER_IMAGE_COLOR;	//残像モデルのエミッシブカラー
};