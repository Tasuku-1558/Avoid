#pragma once

#include "SceneBase.h"
#include "Point2D.h"

class TitleScene final : public SceneBase
{
public:
	TitleScene();
	~TitleScene()override;

	void Initialize()override;					//������
	SceneType Update(float deltaTime)override;	//�X�V
	void TitleNameMove();

	void Blink();

	void Draw()override;						//�`��
	
private:
	int TitleImage;			//�^�C�g���摜
	int TitleBackgroundX;	//�^�C�g���w�iX���W
	int TitleBackgroundY;	//�^�C�g���w�iY���W

	char TitleName[14] = { "Just in Avoid" };

	float StartTitleCount;
	float* TitleAnimTime;		//�^�C�g�������A�j���[�V�����J�E���^
	Point2D* TitleNowPos;
};