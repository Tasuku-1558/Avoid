#include "Evaluation.h"
#include "DxLib.h"
#include "InputManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Evaluation::Evaluation()
	: ui(Ui::NOMAL)
	, evaluationGraph()
	, slowScreenGraph(0)
	, displayTime(0.0f)
	, scale(0.0)
	, EVALUATION_NUMBER(4)
	, SLOW_SCREEN_IMAGE_X(0)
	, SLOW_SCREEN_IMAGE_Y(0)
	, EVALUATION_IMAGE_X(500)
	, EVALUATION_IMAGE_Y(500)
	, MAX_DISPLAY_TIME(50.0f)
	, INITIAL_DISPLAY_TIME(0.0f)
	, DISPLAY_TIME_INCREASE(1.0f)
	, MAX_SCALE(1.0)
	, INITIAL_SCALE(0.0)
	, STOP_SCALE(1.0)
	, SCALE_INCREASE(0.9)
	, ANGLE(0.0)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, EXCELLENT_PATH("ExcellentEffect.png")
	, GREAT_PATH("GreatEffect.png")
	, GOOD_PATH("GoodEffect.png")
	, MISS_PATH("MissEffect.png")
	, SLOW_SCREEN_PATH("SlowScreen.png")
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Evaluation::~Evaluation()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void Evaluation::Initialize()
{
	EvaluationImage evaluationImage[] =
	{
		{EXCELLENT_PATH},
		{GREAT_PATH},
		{GOOD_PATH},
		{MISS_PATH},
	};

	//�]���摜�̓ǂݍ���
	for (int i = 0; i < EVALUATION_NUMBER; i++)
	{
		evaluationGraph[i] = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, evaluationImage[i].evaluationPath).c_str());
	}

	//�W�����摜�̓ǂݍ���
	slowScreenGraph	= LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, SLOW_SCREEN_PATH).c_str());
}

/// <summary>
/// �I������
/// </summary>
void Evaluation::Finalize()
{
	for (int i = 0; i < EVALUATION_NUMBER; i++)
	{
		DeleteGraph(evaluationGraph[i]);
	}

	DeleteGraph(slowScreenGraph);
}

/// <summary>
/// ���x�ᑬ���̏W�����̕`�揈��
/// </summary>
void Evaluation::SlowScreenDraw()
{
	DrawGraph(SLOW_SCREEN_IMAGE_X, SLOW_SCREEN_IMAGE_Y, slowScreenGraph, TRUE);
}

/// <summary>
/// �]�������̓���
/// </summary>
/// <param name="evaluationGraph">�]�������̉摜</param>
void Evaluation::ImageMove(int evaluationGraph)
{
	DrawRotaGraph(EVALUATION_IMAGE_X, EVALUATION_IMAGE_Y, scale, ANGLE, evaluationGraph, TRUE);

	scale += SCALE_INCREASE;

	//�ړI�̑傫���ɂȂ�����
	if (scale > MAX_SCALE)
	{
		scale = STOP_SCALE;
		displayTime += DISPLAY_TIME_INCREASE;

		//�ړI�̕\�����Ԃ��o�߂�����
		if (displayTime > MAX_DISPLAY_TIME)
		{
			//�ʏ��Ԃ�
			ui = Ui::NOMAL;

			//�傫���ƕ\�����Ԃ�������
			scale = INITIAL_SCALE;
			displayTime = INITIAL_DISPLAY_TIME;
		}
	}
}

/// <summary>
/// �e�]���̕`�揈��
/// </summary>
void Evaluation::EvaluationDraw()
{
	//�e�]��
	switch (ui)
	{
	case Ui::EXCELLENT:
		SlowScreenDraw();
		ImageMove(evaluationGraph[0]);
		break;

	case Ui::GREAT:
		SlowScreenDraw();
		ImageMove(evaluationGraph[1]);
		break;

	case Ui::GOOD:
		ImageMove(evaluationGraph[2]);
		break;
		
	case Ui::MISS:
		ImageMove(evaluationGraph[3]);
		break;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Evaluation::Draw()
{
	EvaluationDraw();
}