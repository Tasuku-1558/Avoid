#pragma once

//���Ԓᑬ�N���X
//�V���O���g��
class TimeSlow final
{
public:

	static TimeSlow& GetInstance();	//�A�h���X��Ԃ�

	void  SetTimeSlow(bool time);
	bool GetTimeSlow() { return slow; }

private:

	 TimeSlow();
	 TimeSlow(const TimeSlow&);		//�R�s�[�R���X�g���N�^
	~TimeSlow();

	bool slow;
	
};