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

	void SetTimeSlow(const bool slow);

	const bool GetTimeSlow() { return slowFlag; }		//�ᑬ�ɂ��邩���Ȃ�����Ԃ�

private:
	TimeSlow(const TimeSlow&);		//�R�s�[�R���X�g���N�^

	bool slowFlag;					//���Ԃ�ᑬ�ɂ��邩���Ȃ���
	
};