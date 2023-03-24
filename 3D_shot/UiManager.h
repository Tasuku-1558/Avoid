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

	void Draw(PlayScene::GameState gameState, int font, int countDown, int score, int wave);	//�`�揈��

private:

	UiManager(const UiManager&);		//�R�s�[�R���X�g���N�^

	//�摜�̎��
	enum Graphic
	{
		FRAME,			//�g�摜
		FEVER_IMAGE,
		GRAPHIC_AMOUNT,	//�摜�̐�
	};
	
	void Initialize();
	void Finalize();
	void StartGameDraw();
	void GameUIDraw(int font, int countDown, int score, int wave);		//�Q�[������UI�̕`��
	void FrameDraw();					//�������ԁA�X�R�A�̘g�`�揈��
	void FeverImageDraw();				//�t�B�[�o�[���[�hUI�̕`��
	

	int uiHandle[GRAPHIC_AMOUNT];		//�摜�n���h���i�[�p
	bool fever;


	//�萔
	const string FOLDER_PATH;			//�摜�i�[�t�H���_
	const string UI_GRAPHIC_PATH;		//UI�摜
	const string FILENAME_EXTENSION;	//�摜�g���q
	
};