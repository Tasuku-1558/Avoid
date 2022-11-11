#pragma once

#include "DxLib.h"

//”wŒiƒNƒ‰ƒX
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

