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

	void Update(int evaluationGraph);
	void Draw();


	//�]���̎��
	enum class Ui
	{
		NOMAL,		//�ʏ���
		EXCELLENT,	//excellent�]��
		GREAT,		//great�]��
		GOOD,		//good�]��
		MISS,		//miss�]��
	};

	enum class Ui ui;		//�]���̎��

private:

	Evaluation(const Evaluation&);			//�R�s�[�R���X�g���N�^

	void Initialize();
	void Finalize();
	void ImageMove(int evaluationGraph);	//�]�������̓���
	void EvaluationUi();					//�e�]���̕`�揈��
	void SlowUi();							//���x�ᑬ���̏W�����̕`�揈��

	string InputPath(string folderPath,
					 string imagePath);		//�摜�̃p�X�����

	int evaluationGraph[5];					//�]�������̊i�[�p
	int slowScreenGraph;					//���x�ᑬ���̏W����
	float waitTime;							//�]�������̕\������
	float scale;							//�]�������̑傫��


	//�萔
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string EXCELLENT_PATH;		//excellent�摜�̃p�X
	static const string GREAT_PATH;			//great�摜�̃p�X
	static const string GOOD_PATH;			//good�摜�̃p�X
	static const string MISS_PATH;			//miss�摜�̃p�X
	static const string SLOW_SCREEN_PATH;	//�W�����摜�̃p�X
	static const int	EVALUATION_NUMBER;	//�]��������

};