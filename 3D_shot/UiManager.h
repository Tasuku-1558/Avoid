#pragma once

#include <string>
#include "GameScene.h"

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

	struct Wave
	{
		int time;			//�摜��\�����鎞��
		Graphic graphic;	//�摜�̎��
	};

	struct GameUi
	{
		int posX;			//�Q�[��Ui��X���W
		unsigned int color;	//�Q�[��Ui�̃J���[
		char name[30];		//�Q�[��Ui�̃X�R�A��
		int uiType;			//�Q�[��Ui�̎��
	};
	
	void Initialize();						//����������
	void Finalize();						//�I������
	void StartCountDraw(float frame);		//�J�E���g�_�E���`��
	void GameUiDraw(int font, int countDown, int score, int wave);		//�Q�[��Ui�����`��
	void FrameDraw();						//�g�`��
	void WaveDraw(int countDown);			//�E�F�[�u�`��
	void WaveAlpha(Graphic graphic);		//�E�F�[�u�摜�̓��ߏ���

	int uiHandle[GRAPHIC_AMOUNT];			//�摜�n���h���i�[�p
	int numberImage[3];						//�J�E���g�_�E���摜�i�[�p
	int alpha;								//���ߓx
	int inc;								//���߃X�s�\�h
	int displayTime;						//�E�F�[�u�摜�\������
	bool alphaEnd;							//���ߏI���t���O

	//�萔
	const int MAX_ALPHA;					//�ő哧�ߓx
	const int MAX_DISPLAY_TIME;				//�ő�E�F�[�u�摜�\������
	const int INITIAL_DISPLAY_TIME;			//�����̃E�F�[�u�摜�\������
	const int INC_SPEED;					//���߃X�s�[�h
	const int GAME_UI_NUMBER;				//�\������Q�[��Ui�̐�
	const int COUNTDOWN_IMAGE_NUMBER;		//�J�E���g�_�E���摜�̔z��
	const int WAVE_CATEGORY;				//�E�F�[�u�摜�̎��
	const int WAVE2_TIME;					//�E�F�[�u2�摜��\�����鎞��
	const int WAVE3_TIME;					//�E�F�[�u3�摜��\�����鎞��
	const int WAVE4_TIME;					//�E�F�[�u4�摜��\�����鎞��
	const int WAVE5_TIME;					//�E�F�[�u5�摜��\�����鎞��
	const int TOTAL_COUNT;					//�J�E���g�_�E���摜�̑���
	const int LANDSCAPE_COUNT;				//�J�E���g�_�E���摜�̉������̑���
	const int PORTRAIT_COUNT;				//�J�E���g�_�E���摜�̏c�����̑���
	const int SIZE_X;						//�J�E���g�_�E���摜�̈ꖇ������̉��T�C�Y
	const int SIZE_Y;						//�J�E���g�_�E���摜�̏c�T�C�Y
	const int NUMBER_IMAGE_POS_X;			//�J�E���g�_�E���摜��X���W
	const int NUMBER_IMAGE_POS_Y;			//�J�E���g�_�E���摜��Y���W
	const int WAVE_IMAGE_POS_X;				//�E�F�[�u�摜��X���W
	const int WAVE_IMAGE_POS_Y;				//�E�F�[�u�摜��Y���W
	const int TIME_UI_POS_X;				//��������Ui��X���W
	const int SCORE_UI_POS_X;				//�l���X�R�AUi��X���W
	const int WAVE_UI_POS_X;				//�E�F�[�uUi��X���W
	const int GAME_UI_POS_Y;				//�Q�[��Ui��Y���W
	const int FRAME_IMAGE_POS_X;			//�g�摜��X���W
	const int FRAME_IMAGE_POS_Y;			//�g�摜��Y���W

	const unsigned int TIME_UI_COLOR;		//��������Ui�̃J���[
	const unsigned int SCORE_UI_COLOR;		//�l���X�R�AUi�̃J���[
	const unsigned int WAVE_UI_COLOR;		//�E�F�[�uUi�̃J���[

	const string IMAGE_FOLDER_PATH;			//�摜�i�[�t�H���_
	const string UI_GRAPHIC_PATH;			//Ui�摜
	const string COUNTDOWN_GRAPHIC_PATH;	//�����摜�t�@�C���̃p�X
	const string IMAGE_FILENAME_EXTENSION;	//�摜�g���q
};