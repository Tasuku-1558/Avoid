#pragma once

//�V���O���g��
class Score final
{
public:

	static Score& GetInstance();		// �A�h���X��Ԃ�

	//�g�[�^���X�R�A
	void SetScore(int scoreT);
	int  GetScore() { return score; }

	void SetMissScore(int scoreM);
	int  GetMissScore() { return missScore; }

private:

	 Score();
	 Score(const Score&);		//�R�s�[�R���X�g���N�^
	~Score();

	int score;
	int missScore;
};