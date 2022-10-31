#pragma once

#include "SceneBase.h"



class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene()override;

	void Initialize() override;					//������
	void Finalize()override;
	void Activate()override;
	void SetScore();
	void Update(float deltaTime)override;		//�X�V
	void Draw() override;						//�`��

private:
	
	int resultBackGround;		//���U���g�w�i

	int targetScore;
	int scoreR;

};