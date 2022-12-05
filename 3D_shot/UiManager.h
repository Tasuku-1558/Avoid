#pragma once

#include "DxLib.h"
#include "PlayScene.h"
#include <string>		//������^�N���X

class UiManager final
{
public:
	 UiManager();
	~UiManager();

	void Initialize();
	void Finalize();

	void Draw(PlayScene::State state, int frame);


private:
	UiManager(const UiManager&);		//�R�s�[�R���X�g���N�^
	
	void StartGameDraw();
	void FrameDraw();					//�t���[��UI�̕`��
	void FeverImageDraw();				//�t�B�[�o�[���[�hUI�̕`��

	//�ÓI�萔
	static const std::string FOLDER_PATH;			//�摜�i�[�t�H���_
	static const std::string UI_GRAPHIC_PATH;		//UI�摜
	static const std::string FILENAME_EXTENSION;	//�摜�g���q

	//�摜�̎��
	enum Graphic
	{
		FRAME,
		FEVER_IMAGE,
		GRAPHIC_AMOUNT
	};

	//�摜�n���h��
	int uiHandle[GRAPHIC_AMOUNT];
};