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
	void SceneChange();									//�V�[���؂�ւ�
	void ReturnScreen();								//��ʂ�J�ڂ���
	void ResultScore();									//���U���g��ʗp�X�R�A

	//�e��Ԃɉ������X�V����
	void UpdateStart(float deltaTime);					//�Q�[���J�n�O
	void UpdateGame(float deltaTime);					//�Q�[����
	void UpdateFinish(float deltaTime);					//�Q�[���I��
	void UpdateResult(float deltaTime);					//���ʉ��
	void(GameScene::* pUpdate)(float deltaTime);		//Update�֐��|�C���^

	struct Pop
	{
		int popStartTime;	//覐΂̏o���J�n����
		int popEndTime;		//覐΂̏o���I������
		float popCount;		//覐΂̏o���Ԋu
		int wave;			//覐΂�wave
	};

	struct Time
	{
		int stopTime;		//�ꎞ�I�ɐ������Ԃ��~�߂鎞��
		int releaseTime;	//�ꎞ�I�ɐ������Ԃ��������鎞��
	};

	GameState gameState;		//�Q�[���̏��
	int gameTime;				//�Q�[������
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
	bool countDownStop;			//�������Ԃ��~�߂邩�ǂ���


	//�萔
	const int	STOP_TIME_CATEGORY;		//���Ԃ��~�߂���
	const int	TIME_DIVISION;			//���Ԃ�����l
	const int	METEORITE_POP_CATEGORY;	//覐Ώo���̎��
	const int	SCORE_FONT_SIZE;		//�X�R�A�t�H���g�̃T�C�Y
	const int	FONT_SIZE;				//�t�H���g�̃T�C�Y
	const int	FONT_THICK;				//�t�H���g�̑���
	const int	GAME_FINISH_TIME;		//�Q�[���I������
	const int	WAVE1_POP_START_TIME;
	const int	WAVE2_POP_START_TIME;
	const int	WAVE3_POP_START_TIME;
	const int	WAVE4_POP_START_TIME;
	const int	WAVE5_POP_START_TIME;
	const int	WAVE1_POP_END_TIME;
	const int	WAVE2_POP_END_TIME;
	const int	WAVE3_POP_END_TIME;
	const int	WAVE4_POP_END_TIME;
	const int	WAVE5_POP_END_TIME;
	const int	WAVE1;
	const int	WAVE2;
	const int	WAVE3;
	const int	WAVE4;
	const int	WAVE5;
	const int	WAVE2_STOP_TIME;
	const int	WAVE3_STOP_TIME;
	const int	WAVE4_STOP_TIME;
	const int	WAVE5_STOP_TIME;
	const int	WAVE2_RELEASE_TIME;
	const int	WAVE3_RELEASE_TIME;
	const int	WAVE4_RELEASE_TIME;
	const int	WAVE5_RELEASE_TIME;
	const float WAVE1_POP_COUNT;
	const float WAVE2_POP_COUNT;
	const float WAVE3_POP_COUNT;
	const float WAVE4_POP_COUNT;
	const float WAVE5_POP_COUNT;
	const float INITIAL_METEORITE_POP_COUNT;	//������覐Ώo���J�E���g
	const float GAME_START_COUNT;				//�Q�[���J�n�J�E���g
	const float FADE_START_COUNT;				//�t�F�[�h�J�n�J�E���g
};