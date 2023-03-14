#pragma once

#include "DxLib.h"
#include <string>

using namespace std;

/// <summary>
/// 背景クラス
/// </summary>
class BackGround final
{
public:
	BackGround();
	virtual ~BackGround();

    void Update();
    void Draw();

private:
    BackGround(const BackGround&);  //コピーコンストラクタ

    void Initialize();
    void Finalize();

    int backGroundHandle;       //背景動画格納用

    //静的定数
    static const string VIDEO_FOLDER_PATH;	    //videoフォルダまでのパス
    static const string BACK_GROUND_VIDEO_PATH;	//背景動画のパス

};

