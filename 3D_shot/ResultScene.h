#pragma once

#include "SceneBase.h"

class BackGround;

class ResultScene final : public SceneBase
{
public:
	 ResultScene(SceneManager* const sceneManager);
	~ResultScene();

	void Initialize();					//������
	void Finalize();
	void Activate();
	void AcquisitionScore();			//�X�R�A�擾
	void Update(float deltaTime);		//�X�V
	void DisplayScore();				//�l���X�R�A�\��

	void Blink();						//�����𖾖�
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

	void UpdateStart();
	void UpdateGame();
	void UpdateResult();
	void(ResultScene::* pUpdate)();	//Update�֐��|�C���^

	State state;				//�Q�[�����
	int  frame;					//�t���[����

	int totalScore;				//�l���X�R�A
	int excellentCount;			//excellent�̐�
	int greatCount;				//great�̐�
	int goodCount;				//good�̐�
	int missCount;				//miss�̐�

	int count;
};