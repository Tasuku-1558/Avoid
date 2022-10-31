#pragma once

#include "SceneBase.h"



class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene();

	void Initialize();					//初期化
	void Finalize();
	void Activate();
	void SetScore();
	void Update(float deltaTime);		//更新
	void Draw();						//描画

private:
	
	int resultBackGround;		//リザルト背景

	int totalScore;
	int tScore;

	int missScore;
	int mScore;
};