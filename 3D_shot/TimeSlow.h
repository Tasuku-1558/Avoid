#pragma once


//�V���O���g��
class TimeSlow final
{
public:

	static TimeSlow& GetInstance();	//�A�h���X��Ԃ�

	void  SetTimeSlow(float time);
	float GetTimeSlow() { return slow; }

private:

	 TimeSlow();
	 TimeSlow(const TimeSlow&);		//�R�s�[�R���X�g���N�^
	~TimeSlow();

	float slow;
};