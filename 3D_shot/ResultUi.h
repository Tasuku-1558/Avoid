#pragma once

#include <string>

using namespace std;

/// <summary>
/// ���U���g���UI�N���X
/// </summary>
class ResultUi final
{
public:
	ResultUi();
	virtual ~ResultUi();

	void Draw(int scoreFont, 
			  int countFont, 
			  int score, 
			  int excellentCount, 
			  int greatCount, 
			  int goodCount, 
			  int missCount);	//�`�揈��

private:
	ResultUi(const ResultUi&);	//�R�s�[�R���X�g���N�^

	void Initialize();			//����������
	void Blink();				//�J��Ui�摜�̓_��
	void ScoreDraw(int scoreFont, int countFont, int score, int excellentCount, int greatCount, int goodCount, int missCount);	//�X�R�A�\��
	void GaugeDraw(int score);	//�Q�[�W�\��

	struct Score
	{
		int maxDisplayTime;	//�ő�\������
		int posY;			//�X�R�A��Y���W
		unsigned int color;	//�X�R�A�̐F
		int font;			//�Q�[���t�H���g
		char name[30];		//�X�R�A��
		int scoreType;		//�X�R�A�̎��
	};

	int displayTime;			//�X�R�A�\������
	int evaluationImage[3];		//�X�R�A�]��
	int gaugeFrame;				//�Q�[�W�g�i�[�p
	int resultUi;				//�J�ڂ�Ui�摜�i�[�p
	int alpha;					//���ߓx
	int inc;					//���߃X�s�\�h
	float scoreGauge;			//�X�R�A�Q�[�W
	float earnScore;			//�l���X�R�A
	bool displayFlag;			//�]���摜�\���t���O


	//�萔
	const int DECISION_B_LINE;				//B�]�����胉�C��
	const int DECISION_A_LINE;				//A�]�����胉�C��
	const int DECISION_S_LINE;				//S�]�����胉�C��
	const int EVALUATION_NUMBER;			//�]��������
	const int SCORE_DRAW_NUMBER;			//�\������X�R�A��
	const int MAX_ALPHA;					//�ő哧�ߓx
	const int INC_SPEED;					//���߃X�s�[�h
	const int MAX_SCORE_DISPLAY_TIME;		//�ő�X�R�A�\������
	const int MAX_EXCELLENT_DISPLAY_TIME;	//�ő�Excellent�\������
	const int MAX_GREAT_DISPLAY_TIME;		//�ő�Great�\������
	const int MAX_GOOD_DISPLAY_TIME;		//�ő�Good�\������
	const int MAX_MISS_DISPLAY_TIME;		//�ő�Miss�\������
	const int SCORE_POS_X;					//�X�R�A��X���W
	const int SCORE_POS_Y;					//�X�R�A��Y���W
	const int EXCELLENT_POS_Y;				//Excellent��Y���W
	const int GREAT_POS_Y;					//Great��Y���W
	const int GOOD_POS_Y;					//Good��Y���W
	const int MISS_POS_Y;					//Miss��Y���W
	const int EVALUATION_IMAGE_POS_X;		//�]���摜��X���W
	const int EVALUATION_IMAGE_POS_Y;		//�]���摜��Y���W
	const int RESULT_UI_POS_X;				//�J�ڂ�Ui�摜��X���W
	const int RESULT_UI_POS_Y;				//�J�ڂ�Ui�摜��Y���W
	const int TOP_LEFT_VERTEX_POS_X;		//����̒��_X���W
	const int TOP_LEFT_VERTEX_POS_Y;		//����̒��_Y���W
	const int BOTTOM_RIGHT_VERTEX_POS_X;	//�E���̒��_X���W
	const int BOTTOM_RIGHT_VERTEX_POS_Y;	//�E���̒��_Y���W
	const int ADD_POS_X;					//�����̒��_X���W�ɉ�����l
	const int GAUGE_FRAME_POS_X;			//�X�R�A�Q�[�W�g��X���W
	const int GAUGE_FRAME_POS_Y;			//�X�R�A�Q�[�W�g��Y���W

	const unsigned int SCORE_COLOR;			//�X�R�A�̃J���[
	const unsigned int EXCELLENT_COLOR;		//Excellent�̃J���[
	const unsigned int GREAT_COLOR;			//Great�̃J���[
	const unsigned int GOOD_COLOR;			//Good�̃J���[
	const unsigned int MISS_COLOR;			//Miss�̃J���[
	const unsigned int ORANGE;				//�Q�[�W�̃J���[

	const float MAX_SCORE_GAUGE;			//�ő�X�R�A�Q�[�W
	const float GAUGE_INCREASE;				//�X�R�A������
	const float SCORE_DIVISION;				//�l���X�R�A������l

	const double EVALUATION_IMAGE_SCALE;	//�]���摜�̑傫��
	const double EVALUATION_IMAGE_ANGLE;	//�]���摜�̉�]�l

	const string IMAGE_FOLDER_PATH;			//Image�t�H���_�܂ł̃p�X
	const string RESULT_UI_PATH;			//�J�ڂ�Ui�摜�̃p�X
	const string GAUGE_FRAME_PATH;			//�Q�[�W�g�摜�̃p�X
	const string SCORE_B_PATH;				//B�]���摜�̃p�X
	const string SCORE_A_PATH;				//A�]���摜�̃p�X
	const string SCORE_S_PATH;				//S�]���摜�̃p�X
};