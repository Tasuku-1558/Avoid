#pragma once

#include "SceneBase.h"
#include <vector>

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
	std::vector<Meteorite*> meteorite;
	HitChecker* hitChecker;
	UiManager* uiManager;
	EffectManager* effectManager;
	Evaluation* evaluation;
	ScoreEarn* scoreEarn;
	FadeManager* fadeManager;
	ResultUi* resultUi;
	
	void Initialize()override;							//初期化処理
	void EntryMeteorite(Meteorite* newMeteorite);		//隕石を登録
	void DeleteMeteorite(Meteorite* deleteMeteorite);	//隕石を削除
	void MeteoritePop(float deltaTime);					//隕石の出現間隔
	void GameCountDown();								//ゲーム時間計算
	void ResultScore();

	//各状態に応じた更新処理
	void UpdateStart(float deltaTime);					//ゲーム開始前
	void UpdateGame(float deltaTime);					//ゲーム中
	void UpdateFinish(float deltaTime);					//ゲーム終了
	void UpdateResult(float deltaTime);					//結果画面
	void(GameScene::* pUpdate)(float deltaTime);		//Update関数ポインタ
	

	GameState gameState;		//ゲームの状態
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
	int wave;					//ゲームの区分け
	float frame;				//フレーム数
	float meteoritePopCount;	//隕石出現カウント
	bool sceneChangeTitle;		//タイトル画面へ遷移するかどうか
	bool sceneChangeGame;		//ゲーム画面へ遷移するかどうか


	//定数
	const int	GAME_TIME;			//ゲーム時間
	const float GAME_START_COUNT;	//ゲーム開始カウント
	const float FADE_START_COUNT;	//フェード開始カウント
};