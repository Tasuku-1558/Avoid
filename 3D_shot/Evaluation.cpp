#include "Evaluation.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Evaluation::Evaluation()
	: evaluationGraph()
	, slowScreenGraph(0)
	, scale(0.0f)
	, waitTime(0.0f)
	, ui(Ui::NOMAL)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, EXCELLENT_PATH("ExcellentEffect.png")
	, GREAT_PATH("GreatEffect.png")
	, GOOD_PATH("GoodEffect.png")
	, MISS_PATH("MissEffect.png")
	, SLOW_SCREEN_PATH("SlowScreen.png")
	, EVALUATION_NUMBER(4)
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
std::string Evaluation::InputPath(std::string folderPath, std::string imagePath)
{
	return std::string(folderPath + imagePath);
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
void Evaluation::SlowImageDraw()
{
	DrawGraph(0, 0, slowScreenGraph, TRUE);
}

/// <summary>
/// �]�������̓���
/// </summary>
/// <param name="evaluationGraph">�]���摜�i�[</param>
void Evaluation::ImageMove(int evaluationGraph)
{
	DrawRotaGraph(500, 500, scale, 0, evaluationGraph, TRUE);

	scale += 0.9f;

	//�����̑傫����傫������
	if (scale > 1.0f)
	{
		scale = 1.0f;
		waitTime += 1.0f;

		//�\�����Ԃ��o�߂�����
		if (waitTime > 30.0f)
		{
			//�ʏ��Ԃ�
			ui = Ui::NOMAL;

			//�T�C�Y�ƕ\�����Ԃ�������
			scale = 0.0f;
			waitTime = 0.0f;
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
		SlowImageDraw();
		ImageMove(evaluationGraph[0]);
		break;

	case Ui::GREAT:
		SlowImageDraw();
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