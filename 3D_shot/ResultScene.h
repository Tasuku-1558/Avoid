#pragma once

#include "SceneBase.h"


class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene();

	void Initialize();					//‰Šú‰»
	void Finalize();
	void Activate();
	void AcquisitionScore();
	void ScoreCalculation();
	void Update(float deltaTime);		//XV
	void Draw();						//•`‰æ

private:

	int resultBackGround;		//ƒŠƒUƒ‹ƒg”wŒi

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