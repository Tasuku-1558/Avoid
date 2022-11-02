#pragma once

#include "DxLib.h"

//背景クラス
class BackGround final
{
public:
	 BackGround();
	~BackGround();

    void Initialize();
    void Finalize();
    void Activate();
    void Draw();


private:

    //静的定数
    static const float SIZE;                //モデル倍率
    static const VECTOR INITIAL_POSITION;   //初期位置

    VECTOR position;
    int backGroundHandle;
};

