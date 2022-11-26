#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class BackGround;
class SlowScreen;
class Field;
class Player;
class Meteorite;
class HitChecker;
class UiManager;
class Explosion;
class Evaluation;
class EarnScore;


class PlayScene final : public SceneBase
{
public:
	 PlayScene(SceneManager* const sceneManager);
	~PlayScene();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	//���
	enum State
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
	};

private:

	PlayScene(const PlayScene&);		//�R�s�[�R���X�g���N�^

	Camera* camera;
	BackGround* background;
	Field* field;
	Player* player;
	Meteorite* meteorite[32] = { nullptr };
	//std::vector<Meteorite*> meteorite;
	HitChecker* hitChecker;
	UiManager* uiManager;
	Explosion* explosion;
	Evaluation* evaluation;
	EarnScore* earnscore;
	
	void UpdateStart(float deltaTime);				//�J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void DisplayScore();
	void DisplayTime();
	void(PlayScene::* pUpdate)(float deltaTime);	//Update�֐��|�C���^

	State state;				//�Q�[�����
	int  frame;					//�t���[����
	int  startTime;				//�N������
	int  nowTime;				//���݂̎���
	int  countDown;				//��������
	bool meteoritePopFlag;		//覐΂̏o���t���O
	int  targetScore;			//�ڕW�X�R�A
	int  score;					//�l���X�R�A
	int  font;					//UI�t�H���g
	bool slow;


	//�ÓI�萔
	static const int GAMETIME;	//�Q�[������
};