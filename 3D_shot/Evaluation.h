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

//•]‰¿UIƒNƒ‰ƒX
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
	void SlowUi();

	//Še•]‰¿•¶š‚ÌŠi”[—p
	int excellentGraph;
	int greatGraph;
	int goodGraph;
	int missGraph;

	int slowGraph;
	float waitTime;							//•]‰¿•¶š‚Ì•\¦ŠÔ
	float scale;							//•]‰¿•¶š‚Ì‘å‚«‚³
};
