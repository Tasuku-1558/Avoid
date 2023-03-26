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

	void SetTimeSlow(const bool time);
	const bool GetTimeSlow() { return slow; }

private:
	 TimeSlow(const TimeSlow&);		//コピーコンストラクタ

	bool slow;						//時間を低速にするかしないか
	
};