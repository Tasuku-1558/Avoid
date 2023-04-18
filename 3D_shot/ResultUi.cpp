#include "ResultUi.h"
#include "DxLib.h"
#include "InputManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultUi::ResultUi()
	: displayTime(0)
	, evaluationImage()
	, gaugeFrame(0)
	, resultUi(0)
	, alpha(255)
	, inc(-2)
	, scoreGauge(0.0f)
	, earnScore(0.0f)
	, displayFlag(false)
	, DECISION_B_LINE(6900)
	, DECISION_A_LINE(10000)
	, DECISION_S_LINE(13100)
	, EVALUATION_NUMBER(3)
	, SCORE_DRAW_NUMBER(5)
	, MAX_ALPHA(255)
	, INC_SPEED(-1)
	, MAX_SCORE_DISPLAY_TIME(30)
	, MAX_EXCELLENT_DISPLAY_TIME(70)
	, MAX_GREAT_DISPLAY_TIME(110)
	, MAX_GOOD_DISPLAY_TIME(150)
	, MAX_MISS_DISPLAY_TIME(190)
	, SCORE_POS_X(650)
	, SCORE_POS_Y(250)
	, EXCELLENT_POS_Y(400)
	, GREAT_POS_Y(500)
	, GOOD_POS_Y(600)
	, MISS_POS_Y(700)
	, EVALUATION_IMAGE_POS_X(1450)
	, EVALUATION_IMAGE_POS_Y(150)
	, RESULT_UI_POS_X(1150)
	, RESULT_UI_POS_Y(900)
	, TOP_LEFT_VERTEX_POS_X(500)
	, TOP_LEFT_VERTEX_POS_Y(200)
	, BOTTOM_RIGHT_VERTEX_POS_X(500)
	, BOTTOM_RIGHT_VERTEX_POS_Y(117)
	, ADD_POS_X(800)
	, GAUGE_FRAME_POS_X(218)
	, GAUGE_FRAME_POS_Y(-270)
	, SCORE_COLOR(GetColor(255, 69, 0))
	, EXCELLENT_COLOR(GetColor(255, 255, 0))
	, GREAT_COLOR(GetColor(255, 105, 180))
	, GOOD_COLOR(GetColor(175, 238, 238))
	, MISS_COLOR(GetColor(169, 169, 169))
	, ORANGE(GetColor(255, 165, 0))
	, MAX_SCORE_GAUGE(1500.0f)
	, GAUGE_INCREASE(5.0f)
	, EVALUATION_IMAGE_SCALE(1.0f)
	, EVALUATION_IMAGE_ANGLE(0.5f)
	, SCORE_DIVISION(10.0f)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, RESULT_UI_PATH("ResultUi.png")
	, GAUGE_FRAME_PATH("GaugeFrame.png")
	, SCORE_B_PATH("ScoreB.png")
	, SCORE_A_PATH("ScoreA.png")
	, SCORE_S_PATH("ScoreS.png")
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
	//���U���gUI�摜�̓ǂݍ���
	gaugeFrame = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, GAUGE_FRAME_PATH).c_str());

	resultUi = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, RESULT_UI_PATH).c_str());

	evaluationImage[0] = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, SCORE_B_PATH).c_str());

	evaluationImage[1] = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, SCORE_A_PATH).c_str());

	evaluationImage[2] = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, SCORE_S_PATH).c_str());
}

/// <summary>
/// �X�R�A�\��
/// </summary>
/// <param name="scoreFont">�X�R�A�̃t�H���g</param>
/// <param name="countFont">�]���̉񐔂̃t�H���g</param>
/// <param name="score">�Q�[���X�R�A</param>
/// <param name="excellentCount">excellent�̐�</param>
/// <param name="greatCount">great�̐�</param>
/// <param name="goodCount">good�̐�</param>
/// <param name="missCount">miss�̐�</param>
void ResultUi::ScoreDraw(int scoreFont, int countFont, int score, int excellentCount, int greatCount, int goodCount, int missCount)
{
	displayTime++;

	Score s[] = 
	{
		{MAX_SCORE_DISPLAY_TIME,	 SCORE_POS_Y,	  SCORE_COLOR,	   scoreFont, "SCORE : %d",			  score},
		{MAX_EXCELLENT_DISPLAY_TIME, EXCELLENT_POS_Y, EXCELLENT_COLOR, countFont, "Excellent   �~  %d",	  excellentCount},
		{MAX_GREAT_DISPLAY_TIME,	 GREAT_POS_Y,	  GREAT_COLOR,	   countFont, "Great         �~  %d", greatCount},
		{MAX_GOOD_DISPLAY_TIME,		 GOOD_POS_Y,	  GOOD_COLOR,	   countFont, "Good          �~  %d", goodCount},
		{MAX_MISS_DISPLAY_TIME,		 MISS_POS_Y,	  MISS_COLOR,	   countFont, "Miss          �~  %d", missCount},
	};

	for (int i = 0; i < SCORE_DRAW_NUMBER; i++)
	{
		if (displayTime > s[i].maxDisplayTime)
		{
			DrawFormatStringToHandle(SCORE_POS_X, s[i].posY, s[i].color, s[i].font, s[i].name, s[i].scoreType);
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
	DrawBox(TOP_LEFT_VERTEX_POS_X,
			TOP_LEFT_VERTEX_POS_Y,
			(float)BOTTOM_RIGHT_VERTEX_POS_X + (float)ADD_POS_X * (scoreGauge / MAX_SCORE_GAUGE),
			BOTTOM_RIGHT_VERTEX_POS_Y, ORANGE, TRUE);

	//�g�`��
	DrawGraph(GAUGE_FRAME_POS_X, GAUGE_FRAME_POS_Y, gaugeFrame, TRUE);

	earnScore = (score / SCORE_DIVISION);

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
		DrawRotaGraph(EVALUATION_IMAGE_POS_X, EVALUATION_IMAGE_POS_Y, EVALUATION_IMAGE_SCALE, EVALUATION_IMAGE_ANGLE, evaluationImage[0], TRUE);
	}

	//A����
	if (score > DECISION_A_LINE && displayFlag)
	{
		DrawRotaGraph(EVALUATION_IMAGE_POS_X, EVALUATION_IMAGE_POS_Y, EVALUATION_IMAGE_SCALE, EVALUATION_IMAGE_ANGLE, evaluationImage[1], TRUE);
	}

	//S����
	if (score > DECISION_S_LINE && displayFlag)
	{
		DrawRotaGraph(EVALUATION_IMAGE_POS_X, EVALUATION_IMAGE_POS_Y, EVALUATION_IMAGE_SCALE, EVALUATION_IMAGE_ANGLE, evaluationImage[2], TRUE);
	}
}

/// <summary>
/// �J��Ui�摜�̓_��
/// </summary>
void ResultUi::Blink()
{
	if (alpha > MAX_ALPHA && inc > 0 ||
		alpha < 0 && inc < 0)
	{
		inc *= INC_SPEED;
	}

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawGraph(RESULT_UI_POS_X, RESULT_UI_POS_Y, resultUi, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="scoreFont">�X�R�A�̃t�H���g</param>
/// <param name="countFont">�]���̉񐔂̃t�H���g</param>
/// <param name="score">�Q�[���X�R�A</param>
/// <param name="excellentCount">excellent�̐�</param>
/// <param name="greatCount">great�̐�</param>
/// <param name="goodCount">good�̐�</param>
/// <param name="missCount">miss�̐�</param>
void ResultUi::Draw(int scoreFont, int countFont, int score, int excellentCount, int greatCount, int goodCount, int missCount)
{
	ScoreDraw(scoreFont, countFont, score, excellentCount, greatCount, goodCount, missCount);

	GaugeDraw(score);

	Blink();
}