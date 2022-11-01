#pragma once

#include "SceneBase.h"


class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene();

	void Initialize();					//������
	void Finalize();
	void Activate();
	void AcquisitionScore();
	void ScoreCalculation();
	void Update(float deltaTime);		//�X�V
	void Draw();						//�`��

private:

	int resultBackGround;		//���U���g�w�i

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