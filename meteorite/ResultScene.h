#pragma once

#include "SceneBase.h"

class ResultScene final : public SceneBase
{
public:
	ResultScene();
	~ResultScene()override;

	void Initialize()override;					//������
	SceneType Update(float deltaTime)override;	//�X�V
	void Draw()override;						//�`��

private:
	
};