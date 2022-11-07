#pragma once

//時間低速クラス
//シングルトン
class TimeSlow final
{
public:

	static TimeSlow& GetInstance();	//アドレスを返す

	void  SetTimeSlow(float time);
	float GetTimeSlow() { return slow; }

private:

	 TimeSlow();
	 TimeSlow(const TimeSlow&);		//コピーコンストラクタ
	~TimeSlow();

	float slow;
};