#pragma once

#include "SceneBase.h"

class PlayScene final : public SceneBase
{
public:
	PlayScene();
	~PlayScene()override;

	void Initialize()override;
	SceneType Update(float deltaTime)override;
	void Draw()override;
	
private:
	class Camera* camera;
	class Player* player;
	class Meteorite* meteorite[10] = { nullptr };/*[Meteorite::METEORITE_ARRAY_NUMBER10] = { nullptr };*/
	
	int StartTime;				//起動時間
	int NowTime;				//現在の時間
	int CountDown;				//制限時間
	bool MeteoritePopFlag;		//隕石の出現フラグ

	int GameBackground;			//ゲーム背景

	int x;
	int y;
	double Direction = 0.0f;

	int TargetScore;			//目標スコア
	int Score;
	
	
	//静的定数
	static const int GameTime;	//ゲーム時間
};