#include "Evaluation.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Evaluation::Evaluation()
	: evaluationGraph()
	, slowScreenGraph(0)
	, scale(0.0f)
	, displayTime(0.0f)
	, ui(Ui::NOMAL)
	, EVALUATION_NUMBER(4)
	, MAX_SCALE(1.0f)
	, MAX_DISPLAY_TIME(50.0f)
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
	//�]���摜�̓ǂݍ���
	evaluationGraph[0] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, EXCELLENT_PATH).c_str());

	evaluationGraph[1] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, GREAT_PATH).c_str());

	evaluationGraph[2] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, GOOD_PATH).c_str());

	evaluationGraph[3] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, MISS_PATH).c_str());

	//�W�����摜�̓ǂݍ���
	slowScreenGraph	= LoadGraph(InputPath(IMAGE_FOLDER_PATH, SLOW_SCREEN_PATH).c_str());
}

/// <summary>
/// �摜�̃p�X�����
/// </summary>
/// <param name="folderPath">�t�H���_�܂ł̃p�X</param>
/// <param name="imagePath">�摜�̃p�X</param>
/// <returns></returns>
string Evaluation::InputPath(string folderPath, string imagePath)
{
	return string(folderPath + imagePath);
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
	DrawGraph(0, 0, slowScreenGraph, TRUE);
}

/// <summary>
/// �]�������̓���
/// </summary>
/// <param name="evaluationGraph">�]���摜</param>
void Evaluation::ImageMove(int evaluationGraph)
{
	DrawRotaGraph(500, 500, scale, 0, evaluationGraph, TRUE);

	scale += 0.9f;

	//�ړI�̑傫���ɂȂ�����
	if (scale > MAX_SCALE)
	{
		scale = 1.0f;
		displayTime += 1.0f;

		//�\�����Ԃ��o�߂�����
		if (displayTime > MAX_DISPLAY_TIME)
		{
			//�ʏ��Ԃ�
			ui = Ui::NOMAL;

			//�T�C�Y�ƕ\�����Ԃ�������
			scale = 0.0f;
			displayTime = 0.0f;
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