#pragma once

#include "DxLib.h"
#include <string>

using namespace std;

/// <summary>
/// wiNX
/// </summary>
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

    int backGroundHandle;       //wi®æi[p


    //ÃIè
    static const string VIDEO_FOLDER_PATH;	    //videotH_ÜÅÌpX
    static const string BACK_GROUND_VIDEO_PATH;	//wi®æÌpX

};

