#pragma once

#include "SceneBase.h"

class Camera;
class Player;
class Meteorite;
class MeteoriteManager;
class HitChecker;
class Explosion;
class Evaluation;


class PlayScene final : public SceneBase
{
public:
	 PlayScene(SceneManager* const sceneManager);
	~PlayScene()override;

	void Initialize() override;
	void Finalize()override;
	void Activate()override;
	void Update(float deltaTime)override;
	void Draw() override;

private:
	Camera* camera;
	Player* player;
	Meteorite* meteorite[54] = { nullptr };
	MeteoriteManager* meteoriteManager;
	HitChecker* hitchecker;
	Explosion* explosion;
	Evaluation* evaluation;
	
	int  startTime;				//起動時間
	int  nowTime;				//現在の時間
	int  countDown;				//制限時間
	bool meteoritePopFlag;		//隕石の出現フラグ
	int  gameBackGround;		//ゲーム画面背景
	int  targetScore;			//目標スコア
	int  score;					//獲得スコア
	
	//デバック用
	int x;
	int y;
	double Direction = 0.0f;

	
	//静的定数
	static const int GAMETIME;	//ゲーム時間
};