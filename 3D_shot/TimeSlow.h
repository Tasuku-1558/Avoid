#pragma once

/// <summary>
/// ���Ԓᑬ�N���X
/// �V���O���g��
/// </summary>
class TimeSlow final
{
public:

	static TimeSlow& GetInstance();		//�A�h���X��Ԃ�

	void SetTimeSlow(const bool slow);	//�ᑬ���邩���Ȃ������Z�b�g����

	const bool GetTimeSlow() { return slowFlag; }	//�ᑬ�ɂ��邩���Ȃ�����Ԃ�

private:
	TimeSlow();
	TimeSlow(const TimeSlow&);		//�R�s�[�R���X�g���N�^
	virtual ~TimeSlow();

	bool slowFlag;	//���Ԃ�ᑬ�ɂ��邩���Ȃ���
};