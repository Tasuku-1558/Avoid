#pragma once

#include "SceneBase.h"
#include "Point2D.h"

class TitleScene final : public SceneBase
{
public:
	TitleScene();
	~TitleScene()override;

	void Initialize()override;					//初期化
	SceneType Update(float deltaTime)override;	//更新
	void TitleNameMove();

	void BlinkingString(int x, int y, char* str);

	void Draw()override;						//描画
	
private:
	int TitleImage;			//タイトル画像
	int TitleBackgroundX;	//タイトル背景X座標
	int TitleBackgroundY;	//タイトル背景Y座標

	char TitleName[14] = { "Just in Avoid" };

	float StartTitleCount;
	float* TitleAnimTime;		//タイトル文字アニメーションカウンタ
	Point2D* TitleNowPos;
};