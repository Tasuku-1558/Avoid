#pragma once


/// <summary>
/// ���Ԓᑬ�N���X
/// �V���O���g��
/// </summary>
class TimeSlow final
{
public:
	TimeSlow();
	virtual ~TimeSlow();


	static TimeSlow& GetInstance();	//�A�h���X��Ԃ�

	void SetTimeSlow(const bool time);
	const bool GetTimeSlow() { return slow; }

private:
	 TimeSlow(const TimeSlow&);		//�R�s�[�R���X�g���N�^

	bool slow;						//���Ԃ�ᑬ�ɂ��邩���Ȃ���
	
};