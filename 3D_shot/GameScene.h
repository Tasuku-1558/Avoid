#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class Field;
class Player;
class Meteorite;
class HitChecker;
class UiManager;
class EffectManager;
class Evaluation;
class ScoreEarn;
class FadeManager;

/// <summary>
/// �Q�[���V�[���N���X
/// </summary>
class GameScene final : public SceneBase
{
public:
	GameScene();
	virtual ~GameScene();

	SceneType Update(float deltaTime)override;		//�X�V����
	void Draw()override;							//�`�揈��


	//�Q�[���̏��
	enum class GameState
	{
		START,		//�J�n�O
		GAME,		//�Q�[����
		/*WAVE1,
		WAVE2,
		WAVE3,
		WAVE4,*/
		FINALWAVE,	//�ŏIWave
		FINISH,		//�Q�[���I��
		RESULT,		//���ʉ��
	};

private:

	GameScene(const GameScene&);		//�R�s�[�R���X�g���N�^

	Camera* camera;
	Light* light;
	BackGround* backGround;
	Field* field;
	Player* player;
	std::vector<Meteorite*> meteorite;
	HitChecker* hitChecker;
	UiManager* uiManager;
	EffectManager* effectManager;
	Evaluation* evaluation;
	ScoreEarn* scoreEarn;
	FadeManager* fadeManager;
	
	void Initialize()override;							//����������
	void GameCountDown();								//�Q�[�����Ԍv�Z
	void EntryMeteorite(Meteorite* newMeteorite);		//覐΂�o�^
	void DeleteMeteorite(Meteorite* deleteMeteorite);	//覐΂��폜
	void MeteoritePop(float deltaTime);					//覐΂̏o���Ԋu
	void DrawResult();

	//�e��Ԃɉ������X�V����
	void UpdateStart(float deltaTime);					//�Q�[���J�n�O
	void UpdateWave1(float deltaTime);					//Wave1
	void UpdateFinal(float deltaTime);					//�t�@�C�i��Wave
	void GameFinish(float deltaTime);					//�Q�[���I��
	void UpdateResult(float deltaTime);					//���ʉ��
	void(GameScene::* pUpdate)(float deltaTime);		//Update�֐��|�C���^
	

	GameState gameState;		//�Q�[���̏��
	int  startTime;				//�N������
	int  nowTime;				//���ݎ���
	int  countDown;				//��������
	int  targetScore;			//�ڕW�X�R�A
	int  score;					//�l���X�R�A
	int  font;					//�Q�[���t�H���g
	int  wave;					//�Q�[���̋敪��
	int shadowMapHandle;		//�V���h�E�}�b�v�n���h��
	float frame;				//�t���[����
	float meteoritePopCount;	//覐Ώo���J�E���g
	bool slow;					//���Ԃ��X���[�ɂ��邩
	

	//�萔
	const int GAME_TIME;		//�Q�[������
};