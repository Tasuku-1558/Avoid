#pragma once

#include "SceneBase.h"

class ResultScene final : public SceneBase
{
public:
	ResultScene();
	~ResultScene()override;

	void Initialize()override;					//初期化
	SceneType Update(float deltaTime)override;	//更新
	void Draw()override;						//描画

private:
	
};