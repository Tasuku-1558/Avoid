#pragma once

#include "SceneBase.h"



class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene()override;

	void Initialize() override;					//‰Šú‰»
	void Finalize()override;
	void Activate()override;
	void SetScore();
	void Update(float deltaTime)override;		//XV
	void Draw() override;						//•`‰æ

private:
	
	int resultBackGround;		//ƒŠƒUƒ‹ƒg”wŒi

	int targetScore;
	int scoreR;

};