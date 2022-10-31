#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Player;
class Meteorite;
class MeteoriteManager;
class HitChecker;
class Explosion;
class Evaluation;
class EarnScore;


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

	//状態
	enum State
	{
		START,	//開始前
		GAME,	//ゲーム中
	};

private:
	Camera* camera;
	Player* player;
	Meteorite* meteorite[54] = { nullptr };
	//std::vector<Meteorite*> meteorite;
	MeteoriteManager* meteoriteManager;
	HitChecker* hitchecker;
	Explosion* explosion;
	Evaluation* evaluation;
	EarnScore* earnscore;
	
	void UpdateStart();
	void UpdateGame();
	void(PlayScene::* pUpdate)();	//Update関数ポインタ

	State state;				//ゲーム状態
	int  startTime;				//起動時間
	int  nowTime;				//現在の時間
	int  countDown;				//制限時間
	bool meteoritePopFlag;		//隕石の出現フラグ
	int  gameBackGround;		//ゲーム画面背景
	int  targetScore;			//目標スコア
	int  score;					//獲得スコア
	
	
	//静的定数
	static const int GAMETIME;	//ゲーム時間
};