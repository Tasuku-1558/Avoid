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
	void Update(float deltaTime) override;		//�X�V
	void Draw() override;						//�`��

private:
	HitChecker* hitchecker;

	int resultImage;			//���U���g�摜
	int resultBackgroundX;		//���U���g�w�iX���W
	int resultBackgroundY;		//���U���g�w�iY���W

	int targetScore;
	int score;

};