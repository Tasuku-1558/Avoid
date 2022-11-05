#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class BackGround;
class Field;
class Player;
class Meteorite;
class MeteoriteManager;
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
		FEVER,
	};

private:

	PlayScene(const PlayScene&);		//�R�s�[�R���X�g���N�^

	Camera* camera;
	BackGround* background;
	Field* field;
	Player* player;
	Meteorite* meteorite[54] = { nullptr };
	//std::vector<Meteorite*> meteorite;
	MeteoriteManager* meteoriteManager;
	HitChecker* hitChecker;
	UiManager* uiManager;
	Explosion* explosion;
	Evaluation* evaluation;
	EarnScore* earnscore;
	
	void UpdateStart(float deltaTime);
	void UpdateGame(float deltaTime);
	void UpdateFever(float deltaTime);
	void(PlayScene::* pUpdate)(float deltaTime);	//Update�֐��|�C���^

	State state;				//�Q�[�����
	int  frame;					//�t���[����
	int  startTime;				//�N������
	int  nowTime;				//���݂̎���
	int  countDown;				//��������
	bool meteoritePopFlag;		//覐΂̏o���t���O
	int  targetScore;			//�ڕW�X�R�A
	int  score;					//�l���X�R�A
	float feverGauge;			//�t�B�[�o�[�p�Q�[�W
	
	//�ÓI�萔
	static const int GAMETIME;	//�Q�[������
};