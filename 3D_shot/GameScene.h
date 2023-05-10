#pragma once

#include <vector>
#include "SceneBase.h"

class Camera;
class Light;
class BackGround;
class Field;
class Player;
class Meteorite;
class HitChecker;
class UiManager;
class EffectManager;
class Evaluation;
class ScoreEarn;
class FadeManager;
class ResultUi;

/// <summary>
/// ゲームシーンクラス
/// </summary>
class GameScene final : public SceneBase
{
public:
	GameScene();
	virtual ~GameScene();

	SceneType Update(float deltaTime)override;		//更新処理
	void Draw()override;							//描画処理

	//ゲームの状態
	enum class GameState
	{
		START,		//ゲーム開始前
		GAME,		//ゲーム中
		FINISH,		//ゲーム終了
		RESULT,		//結果画面
	};

private:
	GameScene(const GameScene&);		//コピーコンストラクタ

	Camera* camera;
	Light* light;
	BackGround* backGround;
	Field* field;
	Player* player;
	Meteorite* meteorite;
	HitChecker* hitChecker;
	UiManager* uiManager;
	EffectManager* effectManager;
	Evaluation* evaluation;
	ScoreEarn* scoreEarn;
	FadeManager* fadeManager;
	ResultUi* resultUi;

	std::vector<Meteorite*> activeMeteorite;

	void Initialize()override;									//初期化処理
	void MeteoritePop(float deltaTime);							//隕石の出現間隔
	void GameCountDown();										//ゲーム時間計算
	void SceneChange();											//シーン切り替え
	void ReturnScreen();										//画面を遷移する
	void ResultScore();											//リザルト画面用スコア
	void InputScene(bool sceneChange, SceneType sceneType);		//シーンの入力

	//各状態に応じた更新処理
	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void UpdateFinish(float deltaTime);				//ゲーム終了
	void UpdateResult(float deltaTime);				//結果画面
	void(GameScene::* pUpdate)(float deltaTime);	//Update関数ポインタ

	struct Pop
	{
		int popStartTime;	//隕石の出現開始時間
		int popEndTime;		//隕石の出現終了時間
		float popCount;		//隕石の出現間隔
		int wave;			//隕石のwave
	};

	struct Time
	{
		int stopTime;		//制限時間を止める時間
		int releaseTime;	//制限時間を解除する時間
	};

	GameState gameState;		//ゲームの状態
	int gameTime;				//ゲーム時間
	int startTime;				//起動時間
	int nowTime;				//現在時間
	int countDown;				//制限時間
	int score;					//獲得スコア
	int excellentCount;			//excellentの数
	int greatCount;				//greatの数
	int goodCount;				//goodの数
	int missCount;				//missの数
	int scoreFont;				//スコアフォント
	int fontHandle;				//フォントハンドル
	int wave;					//隕石のウェーブ
	float frame;				//フレーム数
	float meteoritePopCount;	//隕石出現カウント
	bool sceneChangeTitle;		//タイトル画面へ遷移するかどうか
	bool sceneChangeGame;		//ゲーム画面へ遷移するかどうか
	bool countDownStop;			//制限時間を止めるかどうか


	//定数
	const int	STOP_TIME_CATEGORY;		//時間を止める種類
	const int	TIME_DIVISION;			//時間を割る値
	const int	METEORITE_POP_CATEGORY;	//隕石出現の種類
	const int	SCORE_FONT_SIZE;		//スコアフォントのサイズ
	const int	FONT_SIZE;				//フォントのサイズ
	const int	FONT_THICK;				//フォントの太さ
	const int	GAME_FINISH_TIME;		//ゲーム終了時間
	const int	WAVE1_POP_START_TIME;	//ウェーブ1の隕石の出現開始時間
	const int	WAVE2_POP_START_TIME;	//ウェーブ2の隕石の出現開始時間
	const int	WAVE3_POP_START_TIME;	//ウェーブ3の隕石の出現開始時間
	const int	WAVE4_POP_START_TIME;	//ウェーブ4の隕石の出現開始時間
	const int	WAVE5_POP_START_TIME;	//ウェーブ5の隕石の出現開始時間
	const int	WAVE1_POP_END_TIME;		//ウェーブ1の隕石の出現終了時間
	const int	WAVE2_POP_END_TIME;		//ウェーブ2の隕石の出現終了時間
	const int	WAVE3_POP_END_TIME;		//ウェーブ3の隕石の出現終了時間
	const int	WAVE4_POP_END_TIME;		//ウェーブ4の隕石の出現終了時間
	const int	WAVE5_POP_END_TIME;		//ウェーブ5の隕石の出現終了時間
	const int	WAVE1;					//隕石のウェーブ1
	const int	WAVE2;					//隕石のウェーブ2
	const int	WAVE3;					//隕石のウェーブ3
	const int	WAVE4;					//隕石のウェーブ4
	const int	WAVE5;					//隕石のウェーブ5
	const int	WAVE2_STOP_TIME;		//ウェーブ2の制限時間を止める時間
	const int	WAVE3_STOP_TIME;		//ウェーブ3の制限時間を止める時間
	const int	WAVE4_STOP_TIME;		//ウェーブ4の制限時間を止める時間
	const int	WAVE5_STOP_TIME;		//ウェーブ5の制限時間を止める時間
	const int	WAVE2_RELEASE_TIME;		//ウェーブ2の制限時間を解除する時間
	const int	WAVE3_RELEASE_TIME;		//ウェーブ3の制限時間を解除する時間
	const int	WAVE4_RELEASE_TIME;		//ウェーブ4の制限時間を解除する時間
	const int	WAVE5_RELEASE_TIME;		//ウェーブ5の制限時間を解除する時間

	const float WAVE1_POP_COUNT;				//ウェーブ1の隕石の出現間隔
	const float WAVE2_POP_COUNT;				//ウェーブ2の隕石の出現間隔
	const float WAVE3_POP_COUNT;				//ウェーブ3の隕石の出現間隔
	const float WAVE4_POP_COUNT;				//ウェーブ4の隕石の出現間隔
	const float WAVE5_POP_COUNT;				//ウェーブ5の隕石の出現間隔
	const float INITIAL_METEORITE_POP_COUNT;	//初期の隕石出現カウント
	const float GAME_START_COUNT;				//ゲーム開始カウント
	const float FADE_START_COUNT;				//フェード開始カウント
	const float INITIAL_FRAME;					//初期のフレーム数
};