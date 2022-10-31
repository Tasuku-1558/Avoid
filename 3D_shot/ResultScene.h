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
	void SetScore();
	void Update(float deltaTime);		//�X�V
	void Draw();						//�`��

private:
	
	int resultBackGround;		//���U���g�w�i

	int totalScore;
	int tScore;

	int missScore;
	int mScore;
};