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
	void SetScore();
	void Update(float deltaTime);		//XV
	void Draw();						//•`‰æ

private:
	
	int resultBackGround;		//ƒŠƒUƒ‹ƒg”wŒi

	int totalScore;
	int tScore;

	int missScore;
	int mScore;
};