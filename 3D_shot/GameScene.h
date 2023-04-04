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
class ResultUi;

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
		START,		//�Q�[���J�n�O
		GAME,		//�Q�[����
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
	ResultUi* resultUi;
	
	void Initialize()override;							//����������
	void EntryMeteorite(Meteorite* newMeteorite);		//覐΂�o�^
	void DeleteMeteorite(Meteorite* deleteMeteorite);	//覐΂��폜
	void MeteoritePop(float deltaTime);					//覐΂̏o���Ԋu
	void GameCountDown();								//�Q�[�����Ԍv�Z
	void ResultScore();

	//�e��Ԃɉ������X�V����
	void UpdateStart(float deltaTime);					//�Q�[���J�n�O
	void UpdateGame(float deltaTime);					//�Q�[����
	void UpdateFinish(float deltaTime);					//�Q�[���I��
	void UpdateResult(float deltaTime);					//���ʉ��
	void(GameScene::* pUpdate)(float deltaTime);		//Update�֐��|�C���^
	

	GameState gameState;		//�Q�[���̏��
	int startTime;				//�N������
	int nowTime;				//���ݎ���
	int countDown;				//��������
	int score;					//�l���X�R�A
	int excellentCount;			//excellent�̐�
	int greatCount;				//great�̐�
	int goodCount;				//good�̐�
	int missCount;				//miss�̐�
	int scoreFont;				//�X�R�A�t�H���g
	int fontHandle;				//�t�H���g�n���h��
	int wave;					//�Q�[���̋敪��
	float frame;				//�t���[����
	float meteoritePopCount;	//覐Ώo���J�E���g
	bool sceneChangeTitle;		//�^�C�g����ʂ֑J�ڂ��邩�ǂ���
	bool sceneChangeGame;		//�Q�[����ʂ֑J�ڂ��邩�ǂ���


	//�萔
	const int	GAME_TIME;			//�Q�[������
	const float GAME_START_COUNT;	//�Q�[���J�n�J�E���g
	const float FADE_START_COUNT;	//�t�F�[�h�J�n�J�E���g
};