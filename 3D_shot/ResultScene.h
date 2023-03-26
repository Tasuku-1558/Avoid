#pragma once

#include "SceneBase.h"
#include <string>

using namespace std;

class BackGround;

/// <summary>
/// ���U���g�V�[���N���X
/// </summary>
class ResultScene final : public SceneBase
{
public:
	ResultScene();
	virtual ~ResultScene();

	SceneType Update(float deltaTime)override;		//�X�V����
	void Draw()override;							//�`�揈��

	//�Q�[���̏��
	enum class State
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
		RESULT, //���U���g��
	};

private:

	ResultScene(const ResultScene&);	//�R�s�[�R���X�g���N�^

	void Initialize()override;			//����������
	void AcquisitionScore();			//�X�R�A�擾
	void DisplayScore();				//�l���X�R�A�\��
	void Blink();						//�����̓_��
	void ScoreGauge();					//�X�R�A�Q�[�W�\��

	void UpdateStart();					//�J�n�O
	void UpdateGame();					//�Q�[����
	void UpdateResult();				//���U���g��
	void(ResultScene::* pUpdate)();		//Update�֐��|�C���^

	BackGround* background;

	State state;				//�Q�[�����
	float frame;					//�t���[����
	int totalScore;				//�l���X�R�A
	int excellentCount;			//excellent�̐�
	int greatCount;				//great�̐�
	int goodCount;				//good�̐�
	int missCount;				//miss�̐�
	int displayCount;			//�X�R�A�\���J�E���g
	int resultUi;				//���v���C�A�^�C�g���ւ�UI
	int scoreFont;				//�l���X�R�A�t�H���g
	int evaluationFont;			//�e�]���t�H���g
	float scoreGauge;			//�X�R�A�Q�[�W
	float scoreMaxGauge;		//�X�R�A�ő�Q�[�W
	int scoreGaugeFrame;		//�X�R�A�Q�[�W�g
	int scoreB;					//B�]���摜�̊i�[�p
	int scoreA;					//A�]���摜�̊i�[�p
	int scoreS;					//S�]���摜�̊i�[�p
	int alpha;					//���ߓx
	int inc;

	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;		//image�t�H���_�܂ł̃p�X
	static const string RESULT_UI_PATH;			//���v���C�A�^�C�g���ւ�UI�摜�̃p�X
	static const string SCORE_GAUGE_PATH;		//�X�R�A�Q�[�W�g�摜�̃p�X
	static const string SCORE_B_PATH;			//B�]���摜�̃p�X
	static const string SCORE_A_PATH;			//A�]���摜�̃p�X
	static const string SCORE_S_PATH;			//S�]���摜�̃p�X

};