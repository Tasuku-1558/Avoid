#pragma once

#include <string>
#include "ObjectBase.h"

using namespace std;

/// <summary>
/// フィールドクラス
/// </summary>
class Field final : public ObjectBase
{
public:
	Field();
	virtual ~Field();

	void Draw();					//描画処理

private:
	Field(const Field&);			//コピーコンストラクタ

	void Initialize();				//初期化処理
	void Finalize();				//終了処理
	void Update(float deltaTime);	//更新処理

	int lineImage;					//判定ライン画像格納用

	//定数
	const float  LINE_CENTER_POSITION;	//ラインの中心座標
	const float  LINE_SIZE;				//ラインのサイズ
	const float  LINE_ANGLE;			//ラインの回転値
	const VECTOR SIZE;					//フィールドモデルの倍率
	const VECTOR POSITION;				//フィールドモデルの位置
	const VECTOR ROTATE;				//フィールドモデルの回転値
	const VECTOR LINE_POSITION;			//ラインの位置
	const string IMAGE_FOLDER_PATH;		//Imageフォルダまでのパス
	const string LINE_PATH;				//ライン画像のパス
};