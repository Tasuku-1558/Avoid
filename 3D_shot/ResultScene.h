#pragma once

#include "SceneBase.h"

class HitChecker;

class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene()override;

	void Initialize() override;					//‰Šú‰»
	void Finalize()override;
	void Activate()override;
	void Update(float deltaTime)override;		//XV
	void Draw() override;						//•`‰æ

private:
	HitChecker* hitchecker;

	int resultBackGround;		//ƒŠƒUƒ‹ƒg”wŒi

	int targetScore;
	int score;

};