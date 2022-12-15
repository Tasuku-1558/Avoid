#pragma once

//�V���O���g��
//�X�R�A���z�N���X
class Score final
{
public:

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

	void Scoring();				//�X�R�A��ڕW�X�R�A�ɑ�������
private:

	 Score();					//�R���X�g���N�^
	 Score(const Score&);		//�R�s�[�R���X�g���N�^
	~Score();					//�f�X�g���N�^

	int score;
	int excellent;
	int great;
	int good;
	int miss;
	int targetScore;
};