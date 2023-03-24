#pragma once

#include "SceneBase.h"
#include <string>

using namespace std;

class BackGround;

/// <summary>
/// リザルトシーンクラス
/// </summary>
class ResultScene final : public SceneBase
{
public:
	ResultScene();
	virtual ~ResultScene();

	SceneType Update(float deltaTime)override;		//更新処理
	void Draw()override;							//描画処理

	//ゲームの状態
	enum class State
	{
		START,	//開始前
		GAME,	//ゲーム中
		RESULT, //リザルト中
	};

private:

	ResultScene(const ResultScene&);	//コピーコンストラクタ

	void Initialize()override;			//初期化処理
	void Activate()override;
	void AcquisitionScore();			//スコア取得
	void DisplayScore();				//獲得スコア表示
	void Blink();						//文字の点滅
	void ScoreGauge();					//スコアゲージ表示

	void UpdateStart();					//開始前
	void UpdateGame();					//ゲーム中
	void UpdateResult();				//リザルト中
	void(ResultScene::* pUpdate)();		//Update関数ポインタ

	BackGround* background;

	State state;				//ゲーム状態
	float frame;					//フレーム数
	int totalScore;				//獲得スコア
	int excellentCount;			//excellentの数
	int greatCount;				//greatの数
	int goodCount;				//goodの数
	int missCount;				//missの数
	int displayCount;			//スコア表示カウント
	int resultUi;				//リプレイ、タイトルへのUI
	int scoreFont;				//獲得スコアフォント
	int evaluationFont;			//各評価フォント
	float scoreGauge;			//スコアゲージ
	float scoreMaxGauge;		//スコア最大ゲージ
	int scoreGaugeFrame;		//スコアゲージ枠
	int scoreB;					//B評価画像の格納用
	int scoreA;					//A評価画像の格納用
	int scoreS;					//S評価画像の格納用
	int alpha;					//透過度
	int inc;

	//静的定数
	static const string IMAGE_FOLDER_PATH;		//imageフォルダまでのパス
	static const string RESULT_UI_PATH;			//リプレイ、タイトルへのUI画像のパス
	static const string SCORE_GAUGE_PATH;		//スコアゲージ枠画像のパス
	static const string SCORE_B_PATH;			//B評価画像のパス
	static const string SCORE_A_PATH;			//A評価画像のパス
	static const string SCORE_S_PATH;			//S評価画像のパス

};