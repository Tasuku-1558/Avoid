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

	void Update(int evaluationGraph);
	void EvaluationUi();
	void Draw();

	enum class UI ui;

private:

	//Še•]‰¿•¶š‚ÌŠi”[—p
	int excellentGraph;
	int greatGraph;
	int goodGraph;
	int missGraph;

	float waitTime;							//•]‰¿•¶š‚Ì•\¦ŠÔ
	float scale;							//•]‰¿•¶š‚Ì‘å‚«‚³

	const int rotation;						//•]‰¿•¶š‚ÌŠp“x
};
