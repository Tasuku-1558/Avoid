#pragma once

#include "SceneBase.h"
#include <string>

using namespace std;

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene final : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	SceneType Update(float deltaTime)override;		//更新処理
	void Draw()override;						//描画処理
	
private:

	TitleScene(const TitleScene&);		//コピーコンストラクタ

	void Initialize()override;			//初期化処理
	void Finalize()override;			//終了処理
	void Activate()override;			//活性化処理
	void Blink();						//文字の点滅

	//タイトルの状態
	enum class SelectState
	{
		START,	//ゲームを始める
		EXIT,	//ゲームを終了する
	};

	SelectState selectState;			//タイトルの状態
	int titleMovie;						//タイトル動画の格納用
	int titleName;						//タイトル名の画像格納用
	int titleUi;						//プレイシーンへ遷移キーのUI格納用
	int alpha;							//透過度
	int inc;
	float frame;						//フレーム数

	//定数
	static const string VIDEO_FOLDER_PATH;	//videoフォルダまでのパス
	static const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const string PLAY_VIDEO_PATH;	//タイトル動画のパス
	static const string TITLENAME_PATH;		//タイトル名の画像のパス
	static const string TITLE_UI_PATH;		//プレイシーンへ遷移キーのUIのパス

};