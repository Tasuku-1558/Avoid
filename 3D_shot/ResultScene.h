#pragma once

#include "SceneBase.h"

class BackGround;

//���U���g�V�[���N���X
class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene();

	void Initialize();					//������
	void Finalize();
	void Activate();
	void Update(float deltaTime);		//�X�V
	void Draw();						//�`��

	//���
	enum State
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
		RESULT, //���U���g��
	};

private:

	ResultScene(const ResultScene&);		//�R�s�[�R���X�g���N�^

	BackGround* background;

	void AcquisitionScore();			//�X�R�A�擾
	void DisplayScore();				//�l���X�R�A�\��
	void Blink();						//�����𖾖�
	void ScoreGauge();					//�X�R�A�Q�[�W�\��
	void UpdateStart();					//�J�n�O
	void UpdateGame();					//�Q�[����
	void UpdateResult();				//���U���g��
	void(ResultScene::* pUpdate)();		//Update�֐��|�C���^

	State state;				//�Q�[�����
	int  frame;					//�t���[����

	int totalScore;				//�l���X�R�A
	int excellentCount;			//excellent�̐�
	int greatCount;				//great�̐�
	int goodCount;				//good�̐�
	int missCount;				//miss�̐�
	int displayCount;			//�X�R�A�\���J�E���g
	int resultUi;
	int scoreFont;				//�l���X�R�A�t�H���g
	int font;
	float scoreGauge;
	int scoreGaugeFrame;
	int scoreB;
	int scoreA;
	int scoreS;
	bool a;
};