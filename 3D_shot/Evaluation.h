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

class Evaluation final
{
public:
	 Evaluation();
	~Evaluation();

	void Initialize();
	void Finalize();

	void Update(int excellentGraph);
	void EvaluationUpdate();
	void Draw();

	enum class UI ui;

private:

	int excellentGraph;
	int greatGraph;
	int goodGraph;
	int missGraph;
	float count;
	float scale;							//�]�������̑傫��
	int imageHandle;

	const int rotation;						//�]�������̉�]�p�x
};
