#pragma once

//�V���O���g��
//���Ԃ�ᑬ�ɂ��邩���Ȃ���
class TimeSlow final
{
public:

	static TimeSlow& GetInstance();	//�A�h���X��Ԃ�

	void  SetTimeSlow(bool time);
	bool  GetTimeSlow() { return slow; }

private:

	 TimeSlow();					//�R���X�g���N�^
	 TimeSlow(const TimeSlow&);		//�R�s�[�R���X�g���N�^
	~TimeSlow();					//�f�X�g���N�^

	bool slow;
	
};