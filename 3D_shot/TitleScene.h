#pragma once

#include "SceneBase.h"

//�^�C�g���V�[���N���X
class TitleScene final : public SceneBase
{
public:
	 TitleScene(SceneManager* const sceneManager);
	~TitleScene();

	void Initialize();					//������
	void Finalize();
	void Activate();
	void Update(float deltaTime);		//�X�V
	void Draw();						//�`��
	
private:

	TitleScene(const TitleScene&);		//�R�s�[�R���X�g���N�^

	void Blink();						//�����𖾖�

	int backGroundHandle;

	int titleName;
	int titleUi;
};