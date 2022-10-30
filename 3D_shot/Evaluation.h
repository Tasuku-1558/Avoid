#pragma once


//�]���̎��
enum class UI
{
	Nomal = 0,			//������
	Excellent,
	Great,
	Good,
	Miss,
};

//�]��UI�N���X
class Evaluation final
{
public:
	 Evaluation();
	~Evaluation();

	void Initialize();
	void Finalize();

	void Update(int evaluationGraph);
	void EvaluationUi();
	void Draw();

	enum class UI ui;

private:

	//�e�]�������̊i�[�p
	int excellentGraph;
	int greatGraph;
	int goodGraph;
	int missGraph;

	float waitTime;							//�]�������̕\������
	float scale;							//�]�������̑傫��

	const int rotation;						//�]�������̊p�x
};
