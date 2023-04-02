#pragma once

/// <summary>
/// 画面効果クラス
/// </summary>
class FadeManager final
{
public:
	FadeManager();
	virtual ~FadeManager();

	void FadeMove();					//画面効果処理
	void FadeReset();					//画面効果リセット
	void Draw();						//描画処理

	const bool FadeEnd() { return fadeEnd; }		//フェードが終了したかを返す

private:
	FadeManager(const FadeManager&);	//コピーコンストラクタ

	int fade;
	int fadeInc;
	bool fadeEnd;		//フェード終了フラグ

	//定数
	const int BLACK;			//フェードのカラー
	const int MAX_FADE;			//最大画面効果値
};