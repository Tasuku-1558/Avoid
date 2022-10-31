#pragma once

#include "SceneBase.h"

class TitleScene final : public SceneBase
{
public:
	 TitleScene(SceneManager* const sceneManager);
	~TitleScene();

	void Initialize();					//初期化
	void Finalize();
	void Activate();
	void Update(float deltaTime);		//更新

	void Blink();								//文字を明滅

	void Draw();						//描画
	
private:

	TitleScene(const TitleScene&);				//コピーコンストラクタ

	int titleImage;			//タイトル画像
	int titleBackgroundX;	//タイトル背景X座標
	int titleBackgroundY;	//タイトル背景Y座標

	int titleName;

	//静的定数
	static const int TITLE_NAME_X;
	static const int TITLE_NAME_Y;
};