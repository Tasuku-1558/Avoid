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

	void Update(int evaluationGraph);
	void EvaluationUi();
	void Draw();

	enum class UI ui;

private:

	//e]¿¶Ìi[p
	int excellentGraph;
	int greatGraph;
	int goodGraph;
	int missGraph;

	float waitTime;							//]¿¶Ì\¦Ô
	float scale;							//]¿¶Ìå«³

	const int rotation;						//]¿¶Ìpx
};
