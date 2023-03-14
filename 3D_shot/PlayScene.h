#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class SlowScreen;
class Field;
class Player;
class Meteorite;
class HitChecker;
class UiManager;
class EffectManager;
class Evaluation;
class ScoreEarn;

/// <summary>
/// プレイシーンクラス
/// </summary>
class PlayScene final : public SceneBase
{
public:
	PlayScene();
	virtual ~PlayScene();

	SceneType Update(float deltaTime)override;
	void Draw()override;


	// ゲーム状態
	enum class GameState
	{
		START,		//開始前
		GAME,		//ゲーム中
		/*WAVE1,
		WAVE2,
		WAVE3,
		WAVE4,*/
		FINALWAVE,	//最終Wave
		FINISH,		//ゲーム終了
		RESULT,		//結果画面
	};

private:

	PlayScene(const PlayScene&);		//コピーコンストラクタ

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
	
	void Initialize()override;
	void Finalize()override;
	void Activate()override;
	void EntryMeteorite(Meteorite* newMeteorite);		//隕石を登録
	void DeleteMeteorite(Meteorite* deleteMeteorite);	//隕石を削除
	void MeteoritePop(float deltaTime);					//隕石の出現間隔

	void UpdateStart(float deltaTime);					//ゲーム開始前
	void UpdateWave1(float deltaTime);					//Wave1
	void UpdateFinal(float deltaTime);					//ファイナルWave
	void GameFinish(float deltaTime);					//ゲーム終了
	void UpdateResult(float deltaTime);					//結果画面
	void(PlayScene::* pUpdate)(float deltaTime);		//Update関数ポインタ
	void GameCountDown();								//ゲーム時間計算
	

	GameState gameState;		//ゲームの状態
	float frame;				//フレーム数
	int  startTime;				//起動時間
	int  nowTime;				//現在時間
	int  countDown;				//制限時間
	int  targetScore;			//目標スコア
	int  score;					//獲得スコア
	int  font;					//ゲームフォント
	bool slow;					//時間をスローにするか
	float meteoritePopCount;	//隕石出現カウント
	int  wave;					//ゲームの区分け
	

	//定数
	const int GAME_TIME;		//ゲーム時間
};