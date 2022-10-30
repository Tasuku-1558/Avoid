#pragma once

#include "SceneBase.h"

class HitChecker;

class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene()override;

	void Initialize() override;					//������
	void Finalize()override;
	void Activate()override;
	void Update(float deltaTime)override;		//�X�V
	void Draw() override;						//�`��

private:
	HitChecker* hitchecker;

	int resultBackGround;		//���U���g�w�i

	int targetScore;
	int score;

};