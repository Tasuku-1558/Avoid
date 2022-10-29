#pragma once


//•]‰¿‚Ìí—Ş
enum class UI
{
	Nomal = 0,			//‰Šú‰»
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

	void Update(int evaluationGraph);
	void EvaluationState();
	void Draw();

	enum class UI ui;

private:

	int excellentGraph;
	int greatGraph;
	int goodGraph;
	int missGraph;
	float count;
	float scale;							//•]‰¿•¶š‚Ì‘å‚«‚³
	int imageHandle;

	const int rotation;						//•]‰¿•¶š‚Ì‰ñ“]Šp“x
};
