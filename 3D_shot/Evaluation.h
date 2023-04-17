#pragma once

#include <string>

using namespace std;

/// <summary>
/// �]��UI�N���X
/// </summary>
class Evaluation final
{
public:
	Evaluation();
	virtual ~Evaluation();

	//�]���̎��
	enum class Ui
	{
		NOMAL,		//�ʏ���
		EXCELLENT,	//excellent�]��
		GREAT,		//great�]��
		GOOD,		//good�]��
		MISS,		//miss�]��
	};

	void Draw();	//�`�揈��

	enum class Ui ui;	//�]���̎��

private:

	Evaluation(const Evaluation&);			//�R�s�[�R���X�g���N�^

	void Initialize();						//����������
	void Finalize();						//�I������
	void ImageMove(int evaluationGraph);	//�]�������̓���
	void EvaluationDraw();					//�e�]���̕`�揈��
	void SlowScreenDraw();					//���x�ᑬ���̏W�����̕`�揈��

	int evaluationGraph[5];					//�]�������摜�̊i�[�p
	int slowScreenGraph;					//�W�����摜�̊i�[�p
	float displayTime;						//�\������
	float scale;							//�]�������̑傫��

	struct EvaluationImage
	{
		string evaluationPath;	//�]���摜�̃p�X
	};

	//�萔
	const int	 EVALUATION_NUMBER;		//�]��������
	const int	 SLOW_SCREEN_IMAGE_X;	//�W�����摜��X���W
	const int	 SLOW_SCREEN_IMAGE_Y;	//�W�����摜��Y���W
	const int	 EVALUATION_IMAGE_X;	//�]�������摜��X���W
	const int	 EVALUATION_IMAGE_Y;	//�]�������摜��Y���W
	const int	 ANGLE;					//�]�������摜�̉�]�l
	const float  MAX_SCALE;				//�ő�̕����̑傫��
	const float  MAX_DISPLAY_TIME;		//�ő�\������
	const float	 STOP_SCALE;			//�~�߂镶���̑傫��
	const float  INITIAL_SCALE;			//�����̕����̑傫��
	const float  INITIAL_DISPLAY_TIME;	//�����̍ő�\������
	const float  SCALE_INCREASE;		//�����̑傫���̑�����
	const float  DISPLAY_TIME_INCREASE;	//�\�����ԑ�����
	const string IMAGE_FOLDER_PATH;		//Image�t�H���_�܂ł̃p�X
	const string EXCELLENT_PATH;		//excellent�摜�̃p�X
	const string GREAT_PATH;			//great�摜�̃p�X
	const string GOOD_PATH;				//good�摜�̃p�X
	const string MISS_PATH;				//miss�摜�̃p�X
	const string SLOW_SCREEN_PATH;		//�W�����摜�̃p�X

};