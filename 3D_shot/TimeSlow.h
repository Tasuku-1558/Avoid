#pragma once

//時間を低速にするかしないか
//シングルトン
class TimeSlow final
{
public:

	static TimeSlow& GetInstance();	//アドレスを返す

	void  SetTimeSlow(bool time);
	bool  GetTimeSlow() { return slow; }

private:

	 TimeSlow();
	 TimeSlow(const TimeSlow&);		//コピーコンストラクタ
	~TimeSlow();

	bool slow;
	
};