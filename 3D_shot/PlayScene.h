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

/// <summary>
/// �v���C�V�[���N���X
/// </summary>
class PlayScene final : public SceneBase
{
public:
	PlayScene(SceneManager* const sceneManager);
	virtual ~PlayScene();

	void Initialize()override;
	void Finalize()override;
	void Activate()override;
	void Update(float deltaTime)override;
	void Draw()override;


	// �Q�[�����
	enum class State
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
		/*WAVE1,
		WAVE2,
		WAVE3,
		WAVE4,*/
		FINALWAVE,
		FINISH,	//�I��
		RESULT	//���ʉ��
	};

private:

	PlayScene(const PlayScene&);		//�R�s�[�R���X�g���N�^

	Camera* camera;
	Light* light;
	BackGround* backGround;
	Field* field;
	Player* player;
	std::vector<Meteorite*> meteorite;
	HitChecker* hitChecker;
	UiManager* uiManager;
	Explosion* explosion;
	Evaluation* evaluation;
	ScoreEarn* scorEearn;
	
	void EntryMeteorite(Meteorite* newMeteorite);		//覐΂�o�^
	void DeleteMeteorite(Meteorite* deleteMeteorite);	//覐΂��폜
	void MeteoritePop(float deltaTime);					//覐΂̏o���Ԋu
	void UpdateStart(float deltaTime);					//�Q�[���J�n�O
	void UpdateGame(float deltaTime);					//�Q�[����
	void UpdateFever(float deltaTime);					//�t�B�[�o�[��
	void(PlayScene::* pUpdate)(float deltaTime);		//Update�֐��|�C���^
	void GameCountDown();								//�Q�[�����Ԍv�Z
	

	State state;				//�Q�[�����
	float frame;				//�t���[����
	int  startTime;				//�N������
	int  nowTime;				//���ݎ���
	int  countDown;				//��������
	int  targetScore;			//�ڕW�X�R�A
	int  score;					//�l���X�R�A
	int  font;					//�Q�[���t�H���g
	bool slow;					//���Ԃ��X���[�ɂ��邩
	float meteoritePopCount;	//覐Ώo���J�E���g
	int  wave;					//�Q�[���̋敪��
	

	//�ÓI�萔
	static const int GAMETIME;	//�Q�[������
};