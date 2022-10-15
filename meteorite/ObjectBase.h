#pragma once

#include "DxLib.h"
#include "math3D.h"
#include "ObjectTag.h"


class ObjectBase
{
public:
	         ObjectBase();		//コンストラクタ
	virtual ~ObjectBase();		//デストラクタ

	//virtual  void Update(float dltaTime) = 0;						//= 0は純粋仮想関数
	virtual void Draw();

	const VECTOR& GetPosition() const; 	//Positionのgetter
	const VECTOR& GetDir() const;		//Dirのgetter

protected:
	VECTOR Position;						//現在の座標
	VECTOR Dir;								//向きベクトル
	int	   ModelHandle;						//モデルハンドル
	
};