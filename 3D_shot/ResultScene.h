#pragma once

#include "SceneBase.h"

class BackGround;

class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene();

	void Initialize();					//初期化
	void Finalize();
	void Activate();
	void AcquisitionScore();
	void ScoreCalculation();
	void Update(float deltaTime);		//更新
	void Draw();						//描画

private:

	BackGround* background;

	int totalScore;
	int score;

	int excellentCount;
	int scoreE;

	int greatCount;
	int scoreG;

	int goodCount;
	int scoreD;

	int missCount;
	int scoreM;
};