#pragma once

#include "SceneBase.h"

class PlayScene;

class TitleScene final : public SceneBase
{
public:
	 TitleScene(SceneManager* const sceneManager);
	~TitleScene();

	void Receive(PlayScene* playScene);

	void Initialize();					//初期化
	void Finalize();
	void Activate();
	void Update(float deltaTime);		//更新
	void Draw();						//描画
	
private:

	TitleScene(const TitleScene&);				//コピーコンストラクタ

	PlayScene* playScene;

	void Blink();						//文字を明滅

	int titleImage;			//タイトル画像
	int titleBackgroundX;	//タイトル背景X座標
	int titleBackgroundY;	//タイトル背景Y座標

	int titleName;
	int titleUi;
};