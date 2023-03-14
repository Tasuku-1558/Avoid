#pragma once

#include "DxLib.h"
#include "PlayScene.h"
#include <string>

using namespace std;

/// <summary>
/// UI�Ǘ��N���X
/// </summary>
class UiManager final
{
public:
	UiManager();
	virtual ~UiManager();

	void Draw(PlayScene::GameState gameState, int font, int countDown, int score, int wave);

private:

	UiManager(const UiManager&);		//�R�s�[�R���X�g���N�^

	//�摜�̎��
	enum Graphic
	{
		FRAME,			//�������ԃt���[���摜
		FEVER_IMAGE,
		GRAPHIC_AMOUNT,	//�摜�̐�
	};
	
	void Initialize();
	void Finalize();
	void StartGameDraw();
	void GameUIDraw(int font, int countDown, int score, int wave);		//�Q�[������UI�̕`��
	void FrameDraw();					//�������ԁA�X�R�A�̘g�`�揈��
	void FeverImageDraw();				//�t�B�[�o�[���[�hUI�̕`��
	

	//�ÓI�萔
	static const string FOLDER_PATH;		//�摜�i�[�t�H���_
	static const string UI_GRAPHIC_PATH;	//UI�摜
	static const string FILENAME_EXTENSION;	//�摜�g���q

	bool fever;
	int uiHandle[GRAPHIC_AMOUNT];					//�摜�n���h���i�[�p
};