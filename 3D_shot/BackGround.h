#pragma once

#include "DxLib.h"

//�w�i�N���X
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

    int backGroundHandle;

};

