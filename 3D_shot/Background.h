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

	//Ã“I’è”
	static const float SIZE;				//ƒ‚ƒfƒ‹”{—¦
	static const VECTOR INITIAL_POSITION;	//‰ŠúˆÊ’u
};