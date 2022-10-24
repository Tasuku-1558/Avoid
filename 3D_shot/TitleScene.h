#pragma once

#include "SceneBase.h"

class TitleScene final : public SceneBase
{
public:
	 TitleScene(SceneManager* const sceneManager);
	~TitleScene()override;

	void Initialize()override;					//������
	void Finalize()override;
	void Activate()override;
	void Update(float deltaTime)override;		//�X�V

	void Blink();								//�����𖾖�

	void Draw()override;						//�`��
	
private:

	TitleScene(const TitleScene&);				//�R�s�[�R���X�g���N�^

	int titleImage;			//�^�C�g���摜
	int titleBackgroundX;	//�^�C�g���w�iX���W
	int titleBackgroundY;	//�^�C�g���w�iY���W

	char titleName[14];

	//�ÓI�萔
	static const int TITLE_NAME_X;
	static const int TITLE_NAME_Y;
};