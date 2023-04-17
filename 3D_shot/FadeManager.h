#pragma once

/// <summary>
/// 画面効果クラス
/// </summary>
class FadeManager final
{
public:
	FadeManager();
	virtual ~FadeManager();

	void FadeMove();	//画面効果処理
	void FadeReset();	//画面効果リセット
	void Draw();		//描画処理

	const bool FadeEnd() { return fadeEnd; }	//フェードが終了したかを返す

private:
	FadeManager(const FadeManager&);	//コピーコンストラクタ

	int fade;		//画面効果値
	int fadeInc;	//画面効果スピード値
	bool fadeEnd;	//画面効果終了フラグ

	//定数
	const int INITIAL_FADE;			//初期の画面効果値
	const int INITIAL_FADE_INC;		//初期の画面効果スピード値
	const int TOP_LEFT_VERTEX_X;	//左上の頂点X座標
	const int TOP_LEFT_VERTEX_Y;	//左上の頂点Y座標
	const int BLACK;				//フェードのカラー
	const int MAX_FADE;				//最大画面効果値
	const int FADE_SPEED;			//画面効果のスピード
};