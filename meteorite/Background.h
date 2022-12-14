#pragma once

#include "DxLib.h"

class Background final
{
public:
	Background();
	~Background();

	void Initialize();
	void Update();
	void Draw();

private:
	VECTOR Position;
	int ModelHandle;

	//静的定数
	static const float SIZE;				//モデル倍率
	static const VECTOR INITIAL_POSITION;	//初期位置
};