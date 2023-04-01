#pragma once

/// <summary>
/// 時間低速クラス
/// シングルトン
/// </summary>
class TimeSlow final
{
public:
	TimeSlow();
	virtual ~TimeSlow();

	static TimeSlow& GetInstance();	//アドレスを返す

	void SetTimeSlow(const bool slow);

	const bool GetTimeSlow() { return slowFlag; }		//低速にするかしないかを返す

private:
	TimeSlow(const TimeSlow&);		//コピーコンストラクタ

	bool slowFlag;					//時間を低速にするかしないか
	
};