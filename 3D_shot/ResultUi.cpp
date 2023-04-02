#include "ResultUi.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultUi::ResultUi()
	: displayCount(0)
	, evaluationImage()
	, gaugeFrame(0)
	, resultUi(0)
	, alpha(255)
	, inc(-2)
	, scoreGauge(0.0f)
	, earnScore(0.0f)
	, displayFlag(false)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, RESULT_UI_PATH("ResultUi.png")
	, GAUGE_FRAME_PATH("GaugeFrame.png")
	, SCORE_B_PATH("ScoreB.png")
	, SCORE_A_PATH("ScoreA.png")
	, SCORE_S_PATH("ScoreS.png")
	, DECISION_B_LINE(6900)
	, DECISION_A_LINE(10000)
	, DECISION_S_LINE(13100)
	, EVALUATION_NUMBER(3)
	, MAX_ALPHA(255)
	, ORANGE(GetColor(255, 165, 0))
	, MAX_SCORE_GAUGE(1500.0f)
	, GAUGE_INCREASE(5.0f)
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultUi::~ResultUi()
{
	DeleteGraph(gaugeFrame);
	DeleteGraph(resultUi);

	for (int i = 0; i < EVALUATION_NUMBER; i++)
	{
		DeleteGraph(evaluationImage[i]);
	}
}

/// <summary>
/// ����������
/// </summary>
void ResultUi::Initialize()
{
	//���U���gUI�̓ǂݍ���
	gaugeFrame = LoadGraph(InputPath(IMAGE_FOLDER_PATH, GAUGE_FRAME_PATH).c_str());

	resultUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_UI_PATH).c_str());

	evaluationImage[0] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, SCORE_B_PATH).c_str());

	evaluationImage[1] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, SCORE_A_PATH).c_str());

	evaluationImage[2] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, SCORE_S_PATH).c_str());
}

/// <summary>
/// �p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
string ResultUi::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

struct Score
{
	int a;
	int posY;
	unsigned int color;
	int font;
	char name[30];
	int b;
};

/// <summary>
/// �X�R�A�\��
/// </summary>
void ResultUi::ScoreDraw(int scoreFont, int countFont, int score, int excellentCount, int greatCount, int goodCount, int missCount)
{
	displayCount++;

	Score s[] = 
	{
		{30,250,GetColor(255, 69, 0),scoreFont,"SCORE : %d",score},
		{70,400,GetColor(255, 255, 0),countFont,"Excellent   �~  %d",excellentCount},
		{110,500,GetColor(255, 105, 180),countFont,"Great         �~  %d",greatCount},
		{150,600,GetColor(175, 238, 238),countFont,"Good          �~  %d",goodCount},
		{190,700,GetColor(169, 169, 169),countFont,"Miss          �~  %d",missCount},
	};

	for (int i = 0; i < 5; i++)
	{
		if (displayCount > s[i].a)
		{
			DrawFormatStringToHandle(650, s[i].posY, s[i].color, s[i].font, s[i].name, s[i].b);
		}
	}
}

/// <summary>
/// �Q�[�W�\��
/// </summary>
/// <param name="score">�l���X�R�A</param>
void ResultUi::GaugeDraw(int score)
{
	//�X�R�A�Q�[�W�`��
	DrawBox(500, 200, 500 + 800 * (scoreGauge / MAX_SCORE_GAUGE), 117, ORANGE, TRUE);

	//�X�R�A�Q�[�W�g�`��
	DrawGraph(218, -270, gaugeFrame, TRUE);

	earnScore = (score / 10.0f);

	//�l���X�R�A�܂ŃQ�[�W�𑝂₷
	if (scoreGauge != earnScore)
	{
		scoreGauge += GAUGE_INCREASE;
	}
	else
	{
		displayFlag = true;
	}

	//�e���胉�C���𒴂��Ă��āA�Q�[�W�𑝂₵�I�������
	//B����
	if (score > DECISION_B_LINE && displayFlag)
	{
		DrawRotaGraph(1450, 150, 1.0f, 0.5, evaluationImage[0], TRUE);
	}

	//A����
	if (score > DECISION_A_LINE && displayFlag)
	{
		DrawRotaGraph(1450, 150, 1.0f, 0.5, evaluationImage[1], TRUE);
	}

	//S����
	if (score > DECISION_S_LINE && displayFlag)
	{
		DrawRotaGraph(1450, 150, 1.0f, 0.5, evaluationImage[2], TRUE);
	}
}

/// <summary>
/// �����̓_��
/// </summary>
void ResultUi::Blink()
{
	if (alpha > MAX_ALPHA && inc > 0 ||
		alpha < 0 && inc < 0)
	{
		inc *= -1;
	}

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawGraph(1150, 900, resultUi, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="scoreFont"></param>
/// <param name="countFont"></param>
/// <param name="score"></param>
/// <param name="excellentCount"></param>
/// <param name="greatCount"></param>
/// <param name="goodCount"></param>
/// <param name="missCount"></param>
void ResultUi::Draw(int scoreFont, int countFont, int score, int excellentCount, int greatCount, int goodCount, int missCount)
{
	ScoreDraw(scoreFont, countFont, score, excellentCount, greatCount, goodCount, missCount);

	GaugeDraw(score);

	Blink();
}