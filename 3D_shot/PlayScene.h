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
class Explosion;
class Evaluation;
class ScoreEarn;

//プレイシーンクラス
class PlayScene final : public SceneBase
{
public:
	 PlayScene(SceneManager* const sceneManager);
	~PlayScene();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	//ゲーム状態
	enum State
	{
		START,	//開始前
		GAME,	//ゲーム中
		FEVER,	//フィーバー中
	};

private:

	PlayScene(const PlayScene&);		//コピーコンストラクタ

	Camera* camera;
	Light* light;
	BackGround* background;
	Field* field;
	Player* player;
	std::vector<Meteorite*> meteorite;
	HitChecker* hitChecker;
	UiManager* uiManager;
	Explosion* explosion;
	Evaluation* evaluation;
	ScoreEarn* scoreearn;
	
	void EntryMeteorite(Meteorite* newMeteorite);		//隕石を登録
	void DeleteMeteorite(Meteorite* deleteMeteorite);	//隕石を削除
	void MeteoritePop(float deltaTime);					//隕石の出現間隔
	void UpdateStart(float deltaTime);					//ゲーム開始前
	void UpdateGame(float deltaTime);					//ゲーム中
	void UpdateFever(float deltaTime);					//フィーバー中
	void(PlayScene::* pUpdate)(float deltaTime);		//Update関数ポインタ
	void GameCountDown();								//ゲーム時間計算
	

	State state;				//ゲーム状態
	int  frame;					//フレーム数
	int  startTime;				//起動時間
	int  nowTime;				//現在時間
	int  countDown;				//制限時間
	int  targetScore;			//目標スコア
	int  score;					//獲得スコア
	int  font;					//UIフォント
	bool slow;					//時間をスローにするか
	float meteoritePopCount;	//隕石出現カウント
	int  wave;
	

	//静的定数
	static const int GAMETIME;	//ゲーム時間
};