#pragma once

#include <string>

using namespace std;

/// <summary>
/// �]���̎��
/// </summary>
enum class UI
{
	NOMAL,
	EXCELLENT,
	GREAT,
	GOOD,
	MISS,
};

/// <summary>
/// �]��UI�N���X
/// </summary>
class Evaluation final
{
public:
	 Evaluation();
	~Evaluation();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(int evaluationGraph);
	void Draw();

	enum class UI ui;

private:

	void EvaluationUi();					//�e�]���̕`�揈��
	void SlowUi();							//���x�ᑬ���̏W�����̕`�揈��

	//�e�]�������̊i�[�p
	int excellentGraph;
	int greatGraph;
	int goodGraph;
	int missGraph;

	int slowScreenGraph;					//���x�ᑬ���̏W����
	float waitTime;							//�]�������̕\������
	float scale;							//�]�������̑傫��


	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string EXCELLENT_PATH;		//excellent�摜�̃p�X
	static const string GREAT_PATH;			//great�摜�̃p�X
	static const string GOOD_PATH;			//good�摜�̃p�X
	static const string MISS_PATH;			//miss�摜�̃p�X
	static const string SLOW_SCREEN_PATH;	//�W�����摜�̃p�X

};