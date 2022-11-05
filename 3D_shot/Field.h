#pragma once

#include "ObjectBase.h"

//フィールドクラス
class Field final : public ObjectBase
{
public:

	 Field();
	~Field();

	void Initialize();
	void Finalize();
	void Activate();
	void Draw();

private:

	VECTOR rotateAngle;

	int line;

	static const VECTOR SIZE;			//モデルの倍率
	static const VECTOR POSITION;		//モデルの位置
	static const VECTOR ROTATE;			//モデルの回転

};