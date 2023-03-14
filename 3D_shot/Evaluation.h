#pragma once

#include <string>

using namespace std;

/// <summary>
/// ]¿UINX
/// </summary>
class Evaluation final
{
public:
	Evaluation();
	virtual ~Evaluation();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(int evaluationGraph);
	void Draw();


	//]¿ÌíÞ
	enum class Ui
	{
		NOMAL,		//ÊíóÔ
		EXCELLENT,	//excellent]¿
		GREAT,		//great]¿
		GOOD,		//good]¿
		MISS,		//miss]¿
	};

	enum class Ui ui;

private:

	void ImageMove(int evaluationGraph);	//]¿¶Ì®«
	void EvaluationUi();					//e]¿Ì`æ
	void SlowUi();							//¬xá¬ÌWüÌ`æ

	string InputPath(string folderPath,	//æÌpXðüÍ
					 string imagePath);

	int evaluationGraph[5];					//]¿¶Ìi[p
	int slowScreenGraph;					//¬xá¬ÌWü
	float waitTime;							//]¿¶Ì\¦Ô
	float scale;							//]¿¶Ìå«³


	//è
	static const string IMAGE_FOLDER_PATH;	//imagetH_ÜÅÌpX
	static const string EXCELLENT_PATH;		//excellentæÌpX
	static const string GREAT_PATH;			//greatæÌpX
	static const string GOOD_PATH;			//goodæÌpX
	static const string MISS_PATH;			//missæÌpX
	static const string SLOW_SCREEN_PATH;	//WüæÌpX
	static const int	EVALUATION_NUMBER;	//]¿¶

};