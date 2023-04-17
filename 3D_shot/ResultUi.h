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
	void Blink();				//�����̓_��
	void ScoreDraw(int scoreFont, int countFont, int score, int excellentCount, int greatCount, int goodCount, int missCount);	//�X�R�A�\��
	void GaugeDraw(int score);	//�Q�[�W�\��

	struct Score
	{
		int maxDisplayTime;	//�ő�X�R�A�\������
		int posY;			//�X�R�A��Y���W
		unsigned int color;	//�X�R�A�̐F
		int font;			//�Q�[���t�H���g
		char name[30];		//�X�R�A��
		int scoreType;		//�X�R�A�̎��
	};

	int displayTime;			//�X�R�A�\������
	int evaluationImage[3];		//�X�R�A�]��
	int gaugeFrame;				//�Q�[�W�g�i�[�p
	int resultUi;				//�J�ڂ�UI�摜�i�[�p
	int alpha;					//���ߓx
	int inc;					//���߃X�s�\�h
	float scoreGauge;			//�X�R�A�Q�[�W
	float earnScore;			//�l���X�R�A
	bool displayFlag;			//�]���摜�\���t���O
	

	//�萔
	const int	 DECISION_B_LINE;		//B�]�����胉�C��
	const int	 DECISION_A_LINE;		//A�]�����胉�C��
	const int	 DECISION_S_LINE;		//S�]�����胉�C��
	const int	 EVALUATION_NUMBER;		//�]��������
	const int	 SCORE_DRAW_NUMBER;		//�\������X�R�A��
	const int	 MAX_ALPHA;				//�ő哧�ߓx
	const int	 INC_SPEED;				//���߃X�s�[�h
	const unsigned int ORANGE;			//�Q�[�W�̃J���[
	const float  MAX_SCORE_GAUGE;		//�ő�X�R�A�Q�[�W
	const float  GAUGE_INCREASE;		//�X�R�A������
	const string IMAGE_FOLDER_PATH;		//Image�t�H���_�܂ł̃p�X
	const string RESULT_UI_PATH;		//�J�ڂ�UI�摜�̃p�X
	const string GAUGE_FRAME_PATH;		//�Q�[�W�g�摜�̃p�X
	const string SCORE_B_PATH;			//B�]���摜�̃p�X
	const string SCORE_A_PATH;			//A�]���摜�̃p�X
	const string SCORE_S_PATH;			//S�]���摜�̃p�X
};