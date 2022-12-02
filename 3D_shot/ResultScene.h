#pragma once

#include "SceneBase.h"

class BackGround;

//リザルトシーンクラス
class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene();

	void Initialize();					//初期化
	void Finalize();
	void Activate();
	void Update(float deltaTime);		//更新
	void Draw();						//描画

	//状態
	enum State
	{
		START,	//開始前
		GAME,	//ゲーム中
		RESULT, //リザルト中
	};

private:

	ResultScene(const ResultScene&);		//コピーコンストラクタ

	BackGround* background;

	void AcquisitionScore();			//スコア取得
	void DisplayScore();				//獲得スコア表示
	void Blink();						//文字を明滅
	void ScoreGauge();					//スコアゲージ表示
	void UpdateStart();					//開始前
	void UpdateGame();					//ゲーム中
	void UpdateResult();				//リザルト中
	void(ResultScene::* pUpdate)();		//Update関数ポインタ

	State state;				//ゲーム状態
	int  frame;					//フレーム数

	int totalScore;				//獲得スコア
	int excellentCount;			//excellentの数
	int greatCount;				//greatの数
	int goodCount;				//goodの数
	int missCount;				//missの数
	int displayCount;			//スコア表示カウント
	int resultUi;
	int scoreFont;				//獲得スコアフォント
	int evaluationFont;			//各評価フォント
	float scoreGauge;
	int scoreGaugeFrame;
	int scoreB;
	int scoreA;
	int scoreS;
	bool a;
};