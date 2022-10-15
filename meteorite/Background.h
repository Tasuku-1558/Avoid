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

	//�ÓI�萔
	static const float SIZE;				//���f���{��
	static const VECTOR INITIAL_POSITION;	//�����ʒu
};