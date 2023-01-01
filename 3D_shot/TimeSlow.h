#pragma once


/// <summary>
/// 時間低速クラス
/// </summary>
class TimeSlow final
{
public:

	static TimeSlow& GetInstance();	//アドレスを返す

	void  SetTimeSlow(bool time);
	bool  GetTimeSlow() { return slow; }

private:

	 TimeSlow();					//コンストラクタ
	 TimeSlow(const TimeSlow&);		//コピーコンストラクタ
	~TimeSlow();					//デストラクタ

	bool slow;						//時間を低速にするかしないか
	
};