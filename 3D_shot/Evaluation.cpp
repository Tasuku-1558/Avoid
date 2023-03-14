#include "Evaluation.h"
#include "DxLib.h"

const string Evaluation::IMAGE_FOLDER_PATH = "data/image/";				//image�t�H���_�܂ł̃p�X
const string Evaluation::EXCELLENT_PATH	   = "ExcellentEffect.png";		//excellent�摜�̃p�X
const string Evaluation::GREAT_PATH		   = "GreatEffect.png";			//great�摜�̃p�X
const string Evaluation::GOOD_PATH		   = "GoodEffect.png";			//good�摜�̃p�X
const string Evaluation::MISS_PATH		   = "MissEffect.png";			//miss�摜�̃p�X
const string Evaluation::SLOW_SCREEN_PATH  = "SlowScreen.png";			//�W�����摜�̃p�X
const int	 Evaluation::EVALUATION_NUMBER = 4;							//�]��������


/// <summary>
/// �R���X�g���N�^
/// </summary>
Evaluation::Evaluation()
	: evaluationGraph()
	, slowScreenGraph(0)
	, scale(0.0f)
	, waitTime(0.0f)
	, ui(Ui::NOMAL)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Evaluation::~Evaluation()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Evaluation::Initialize()
{
	//�摜�̓ǂݍ���
	evaluationGraph[0] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, EXCELLENT_PATH).c_str());

	evaluationGraph[1] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, GREAT_PATH).c_str());

	evaluationGraph[2] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, GOOD_PATH).c_str());

	evaluationGraph[3] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, MISS_PATH).c_str());

	slowScreenGraph	   = LoadGraph(InputPath(IMAGE_FOLDER_PATH, SLOW_SCREEN_PATH).c_str());
}

/// <summary>
/// �摜�̃p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="imagePath"></param>
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
/// ����������
/// </summary>
void Evaluation::Activate()
{
	//�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="evaluationGraph"></param>
void Evaluation::Update(int evaluationGraph)
{
	ImageMove(evaluationGraph);
}

/// <summary>
/// ���x�ᑬ���̏W�����̕`�揈��
/// </summary>
void Evaluation::SlowUi()
{
	DrawGraph(0, 0, slowScreenGraph, TRUE);
}

/// <summary>
/// �]�������̓���
/// </summary>
/// <param name="evaluationGraph"></param>
void Evaluation::ImageMove(int evaluationGraph)
{
	DrawRotaGraph(500, 500, scale, 0, evaluationGraph, TRUE);

	scale += 0.9f;

	//�����̑傫����傫������
	if (scale > 1.0f)
	{
		scale = 1.0f;
		waitTime += 1.0f;

		if (waitTime > 30.0f)
		{
			ui = Ui::NOMAL;
			scale = 0.0f;
			waitTime = 0.0f;
		}
	}
}

/// <summary>
/// �e�]���̕`�揈��
/// </summary>
void Evaluation::EvaluationUi()
{
	switch (ui)
	{
	case Ui::EXCELLENT:
		SlowUi();
		Update(evaluationGraph[0]);
		break;

	case Ui::GREAT:
		SlowUi();
		Update(evaluationGraph[1]);
		break;

	case Ui::GOOD:
		Update(evaluationGraph[2]);
		break;
		
	case Ui::MISS:
		Update(evaluationGraph[3]);
		break;
	}
}

void Evaluation::Draw()
{
	EvaluationUi();
}