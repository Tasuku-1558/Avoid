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

    VECTOR position;
    int backGroundHandle;

    //�ÓI�萔
    static const float SIZE;                //���f���{��
    static const VECTOR INITIAL_POSITION;   //�����ʒu

    
};

