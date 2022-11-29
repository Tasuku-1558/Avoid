#pragma once

//�V���O���g��
class Score final
{
public:

	static Score& GetInstance();		// �A�h���X��Ԃ�

	void Activate();

	//�g�[�^���X�R�A
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


private:

	 Score();
	 Score(const Score&);		//�R�s�[�R���X�g���N�^
	~Score();

	void Scoring();				//�X�R�A��ڕW�X�R�A�ɑ�������

	int score;
	int excellent;
	int great;
	int good;
	int miss;
	int targetScore;
};