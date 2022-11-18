#pragma once


//]¿ÌíÞ
enum class UI
{
	Nomal = 0,			//ú»
	Excellent,
	Great,
	Good,
	Miss,
};

//]¿UINX
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

	void EvaluationUi();

	//e]¿¶Ìi[p
	int excellentGraph;
	int greatGraph;
	int goodGraph;
	int missGraph;

	float waitTime;							//]¿¶Ì\¦Ô
	float scale;							//]¿¶Ìå«³
};
