#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class BackGround;
class SlowScreen;
class Field;
class Player;
class Meteorite;
class HitChecker;
class UiManager;
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

	PlayScene(const PlayScene&);		//コピーコンストラクタ

	Camera* camera;
	BackGround* background;
	Field* field;
	Player* player;
	Meteorite* meteorite[32] = { nullptr };
	//std::vector<Meteorite*> meteorite;
	HitChecker* hitChecker;
	UiManager* uiManager;
	Explosion* explosion;
	Evaluation* evaluation;
	EarnScore* earnscore;
	
	void UpdateStart(float deltaTime);				//開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void DisplayScore();
	void DisplayTime();
	void(PlayScene::* pUpdate)(float deltaTime);	//Update関数ポインタ

	State state;				//ゲーム状態
	int  frame;					//フレーム数
	int  startTime;				//起動時間
	int  nowTime;				//現在の時間
	int  countDown;				//制限時間
	bool meteoritePopFlag;		//隕石の出現フラグ
	int  targetScore;			//目標スコア
	int  score;					//獲得スコア
	int  font;					//UIフォント
	bool slow;


	//静的定数
	static const int GAMETIME;	//ゲーム時間
};