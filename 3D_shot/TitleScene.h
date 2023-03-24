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
	void Activate()override;			//活性化処理
	void Blink();						//文字の点滅

	string InputPath(string folderPath,
					 string path);		//パスを入力

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
	const string VIDEO_FOLDER_PATH;		//videoフォルダまでのパス
	const string IMAGE_FOLDER_PATH;		//imageフォルダまでのパス
	const string PLAY_VIDEO_PATH;		//タイトル動画のパス
	const string TITLENAME_PATH;		//タイトル名の画像のパス
	const string TITLE_UI_PATH;			//プレイシーンへ遷移キーのUIのパス
	const int	 MAX_ALPHA;				//最大透過度
	const int	 VIDEO_PLAYBACK_POSITION;	//タイトル動画の再生位置

};