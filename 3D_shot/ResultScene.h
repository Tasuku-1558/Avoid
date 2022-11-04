#pragma once

#include "SceneBase.h"

class BackGround;

class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene();

	void Initialize();					//初期化
	void Finalize();
	void Activate();
	void AcquisitionScore();			//スコア取得
	void Update(float deltaTime);		//更新
	void DisplayScore();
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

	void UpdateStart();
	void UpdateGame();
	void UpdateResult();
	void(ResultScene::* pUpdate)();	//Update関数ポインタ

	State state;				//ゲーム状態
	int  frame;					//フレーム数

	int totalScore;				//獲得スコア
	int excellentCount;			//excellentの数
	int greatCount;				//greatの数
	int goodCount;				//goodの数
	int missCount;				//missの数

	int count;
};