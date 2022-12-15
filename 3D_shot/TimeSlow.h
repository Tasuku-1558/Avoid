#pragma once

//シングルトン
//時間を低速にするかしないか
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

	bool slow;
	
};