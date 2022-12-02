#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class SlowScreen;
class Field;
class Player;
class Meteorite;
class HitChecker;
class UiManager;
class Explosion;
class Evaluation;
class ScoreEarn;

//�v���C�V�[���N���X
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

	//�Q�[�����
	enum State
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
		FEVER,	//�t�B�[�o�[��
	};

private:

	PlayScene(const PlayScene&);		//�R�s�[�R���X�g���N�^

	Camera* camera;
	Light* light;
	BackGround* background;
	Field* field;
	Player* player;
	std::vector<Meteorite*> meteorite;
	HitChecker* hitChecker;
	UiManager* uiManager;
	Explosion* explosion;
	Evaluation* evaluation;
	ScoreEarn* scoreearn;
	
	void EntryMeteorite(Meteorite* newMeteorite);		//覐΂�o�^
	void DeleteMeteorite(Meteorite* deleteMeteorite);	//覐΂��폜
	void MeteoritePop(float deltaTime);					//覐΂̏o���Ԋu
	void UpdateStart(float deltaTime);					//�Q�[���J�n�O
	void UpdateGame(float deltaTime);					//�Q�[����
	void UpdateFever(float deltaTime);					//�t�B�[�o�[��
	void(PlayScene::* pUpdate)(float deltaTime);		//Update�֐��|�C���^
	void GameCountDown();								//�Q�[�����Ԍv�Z
	

	State state;				//�Q�[�����
	int  frame;					//�t���[����
	int  startTime;				//�N������
	int  nowTime;				//���ݎ���
	int  countDown;				//��������
	int  targetScore;			//�ڕW�X�R�A
	int  score;					//�l���X�R�A
	int  font;					//UI�t�H���g
	bool slow;					//���Ԃ��X���[�ɂ��邩
	float meteoritePopCount;	//覐Ώo���J�E���g

	//�ÓI�萔
	static const int GAMETIME;	//�Q�[������
};