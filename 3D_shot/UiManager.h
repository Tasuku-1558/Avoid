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

	void Draw(GameScene::GameState gameState, 
			  float frame, 
			  int font, 
			  int countDown, 
			  int score, 
			  int wave);	//�`�揈��

	void AlphaReset();		//���߂̏�����

	const bool AlphaEnd() { return alphaEnd; }	//���߂��I����������Ԃ�

private:
	UiManager(const UiManager&);		//�R�s�[�R���X�g���N�^

	//�摜�̎��
	enum Graphic
	{
		FRAME,			//�g�摜
		WAVE2,			//�E�F�[�u2�摜
		WAVE3,			//�E�F�[�u3�摜
		WAVE4,			//�E�F�[�u4�摜
		FINAL_WAVE,		//�ŏI�E�F�[�u�摜
		GRAPHIC_AMOUNT,	//�摜�̐�
	};

	//
	struct Wave
	{
		int time;			//��������
		Graphic graphic;	//�摜�̎��
	};
	
	void Initialize();						//����������
	void Finalize();						//�I������
	void StartCountDraw(float frame);		//�J�E���g�_�E���`��
	void GameUiDraw(int font, int countDown, int score, int wave);		//�Q�[����UI�`��
	void FrameDraw();						//�g�`��
	void WaveDraw(int countDown);			//�E�F�[�u�`��
	void WaveAlpha(Graphic graphic);		//�E�F�[�u�摜�̓��ߏ���

	int uiHandle[GRAPHIC_AMOUNT];		//�摜�n���h���i�[�p
	int numberGraphicHandle[3];			//�J�E���g�_�E���摜�i�[�p
	int alpha;							//���ߓx
	int inc;							//���߃X�s�\�h
	int displayTime;					//�E�F�[�u�摜�\������
	bool alphaEnd;						//���ߏI���t���O

	//�萔
	const int	 MAX_ALPHA;					//�ő哧�ߓx
	const int	 MAX_DISPLAY_TIME;			//�ő�E�F�[�u�摜�\������
	const int	 INC_SPEED;					//���߃X�s�[�h
	const int	 COUNTDOWN_IMAGE_NUMBER;	//�J�E���g�_�E���摜�̔z��
	const int	 WAVE_CATEGORY;				//�E�F�[�u�摜�̎��
	const string IMAGE_FOLDER_PATH;			//�摜�i�[�t�H���_
	const string UI_GRAPHIC_PATH;			//UI�摜
	const string COUNTDOWN_GRAPHIC_PATH;	//�����摜�t�@�C���̃p�X
	const string IMAGE_FILENAME_EXTENSION;	//�摜�g���q

};