#pragma once

/// <summary>
/// 時間低速クラス
/// シングルトン
/// </summary>
class TimeSlow final
{
public:

	static TimeSlow& GetInstance();		//アドレスを返す

	void SetTimeSlow(const bool slow);	//低速するかしないかをセットする

	const bool GetTimeSlow() { return slowFlag; }	//低速にするかしないかを返す

private:
	TimeSlow();
	TimeSlow(const TimeSlow&);		//コピーコンストラクタ
	virtual ~TimeSlow();

	bool slowFlag;	//時間を低速にするかしないか
};