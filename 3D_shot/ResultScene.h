#pragma once

#include "SceneBase.h"

class ResultScene final : public SceneBase
{
public:
	ResultScene();
	~ResultScene()override;

	void Initialize()override;					//初期化
	SceneType Update(float deltaTime)override;	//更新
	void Draw()override;						//描画

private:
	int ResultImage;		//リザルト画像
	int ResultBackgroundX;	//リザルト背景X座標
	int ResultBackgroundY;	//リザルト背景Y座標
};