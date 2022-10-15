#pragma once

#include "SceneBase.h"

class ResultScene final : public SceneBase
{
public:
	ResultScene();
	~ResultScene()override;

	void Initialize()override;					//‰Šú‰»
	SceneType Update(float deltaTime)override;	//XV
	void Draw()override;						//•`‰æ

private:
	
};