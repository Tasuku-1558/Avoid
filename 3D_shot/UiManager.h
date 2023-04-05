#pragma once

#include "GameScene.h"
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

	void Draw(GameScene::GameState gameState, float frame, int font, int countDown, int score, int wave);	//�`�揈��

private:

	UiManager(const UiManager&);		//�R�s�[�R���X�g���N�^

	//�摜�̎��
	enum Graphic
	{
		FRAME,			//�g�摜
		GRAPHIC_AMOUNT,	//�摜�̐�
	};
	
	void Initialize();			//����������
	void Finalize();			//�I������
	void StartCountDraw(float frame);		//�J�E���g�_�E���`��
	void GameUiDraw(int font, int countDown, int score, int wave);		//�Q�[����UI�`��
	void FrameDraw();					//�g�`��

	int uiHandle[GRAPHIC_AMOUNT];		//�摜�n���h���i�[�p
	int numberGraphicHandle[3];			//�J�E���g�_�E���摜�i�[�p

	//�萔
	const int	 COUNTDOWN_IMAGE_NUMBER;	//�J�E���g�_�E���摜�̔z��
	const string FOLDER_PATH;				//�摜�i�[�t�H���_
	const string UI_GRAPHIC_PATH;			//UI�摜
	const string COUNTDOWN_GRAPHIC_PATH;	//�����摜�t�@�C���̃p�X
	const string FILENAME_EXTENSION;		//�摜�g���q

};