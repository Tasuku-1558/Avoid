#pragma once

#include "SceneBase.h"

class PlayScene;

class TitleScene final : public SceneBase
{
public:
	 TitleScene(SceneManager* const sceneManager);
	~TitleScene();

	void Receive(PlayScene* playScene);

	void Initialize();					//������
	void Finalize();
	void Activate();
	void Update(float deltaTime);		//�X�V
	void Draw();						//�`��
	
private:

	TitleScene(const TitleScene&);				//�R�s�[�R���X�g���N�^

	PlayScene* playScene;

	void Blink();						//�����𖾖�

	int titleImage;			//�^�C�g���摜
	int titleBackgroundX;	//�^�C�g���w�iX���W
	int titleBackgroundY;	//�^�C�g���w�iY���W

	int titleName;
	int titleUi;
};