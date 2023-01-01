#pragma once

#include "ObjectBase.h"
#include <string>

using namespace std;

/// <summary>
/// フィールドクラス
/// </summary>
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

	VECTOR rotateAngle;					//回転値格納用
	int lineHandle;						//判定ライン格納用

	//静的定数
	static const VECTOR SIZE;			//モデルの倍率
	static const VECTOR POSITION;		//モデルの位置
	static const VECTOR ROTATE;			//モデルの回転
	static const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const string LINE_PATH;			//ライン画像のパス

};