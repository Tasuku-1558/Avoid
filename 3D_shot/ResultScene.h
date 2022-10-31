#pragma once

#include "SceneBase.h"



class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene()override;

	void Initialize() override;					//初期化
	void Finalize()override;
	void Activate()override;
	void SetScore();
	void Update(float deltaTime)override;		//更新
	void Draw() override;						//描画

private:
	
	int resultBackGround;		//リザルト背景

	int targetScore;
	int scoreR;

};