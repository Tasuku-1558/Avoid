#pragma once


/// <summary>
/// �X�R�A���z�N���X
/// </summary>
class Score final
{
public:
	Score();
	virtual ~Score();


	static Score& GetInstance();		// �A�h���X��Ԃ�

	void Activate();

	//�X�R�A�̍��v
	void SetScore(int totalScore);
	int  GetScore() { return targetScore; }

	//�e�X�R�A�̐�
	void SetExcellentCount(int totalExcellent);
	int  GetExcellentCount() { return excellent; }

	void SetGreatCount(int totalGreat);
	int  GetGreatCount() { return great; }

	void SetGoodCount(int totalGood);
	int  GetGoodCount() { return good; }

	void SetMissCount(int totalMiss);
	int  GetMissCount() { return miss; }

	void Scoring();				//�ڕW�X�R�A�܂ŃX�R�A�𑫂�����

private:
	 Score(const Score&);		//�R�s�[�R���X�g���N�^

	//�e�X�R�A�i�[�p
	int score;
	int excellent;
	int great;
	int good;
	int miss;

	int targetScore;	//�ڕW�X�R�A�܂ŃX�R�A�𑫂���������

	//�萔
	static const int FIRST_SCORE;	//�X�R�A�̏����l

};