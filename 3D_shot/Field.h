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
	virtual ~Field();

	void Draw();				//描画処理

private:
	Field(const Field&);		//コピーコンストラクタ

	void Initialize();			//初期化処理
	void Finalize();			//終了処理

	int lineHandle;				//判定ライン格納用

	//定数
	const string IMAGE_FOLDER_PATH;	//Imageフォルダまでのパス
	const string LINE_PATH;			//ライン画像のパス
	const VECTOR SIZE;				//倍率
	const VECTOR POSITION;			//位置
	const VECTOR ROTATE;			//回転値

};