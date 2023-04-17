#include "GameScene.h"

#include "PreCompiledHeader.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Field.h"
#include "Player.h"
#include "Meteorite.h"
#include "HitChecker.h"
#include "UiManager.h"
#include "Evaluation.h"
#include "ScoreEarn.h"
#include "EffectManager.h"
#include "FadeManager.h"
#include "SoundManager.h"
#include "TimeSlow.h"
#include "ResultUi.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
	: SceneBase(SceneType::GAME)
	, gameState(GameState::START)
	, gameTime(90)
	, startTime(0)
	, nowTime(0)
	, countDown(0)
	, score(0)
	, excellentCount(0)
	, greatCount(0)
	, goodCount(0)
	, missCount(0)
	, scoreFont(0)
	, fontHandle(0)
	, wave(0)
	, frame(0.0f)
	, meteoritePopCount(0.0f)
	, sceneChangeTitle(false)
	, sceneChangeGame(false)
	, pUpdate(nullptr)
	, STOP_TIME_CATEGORY(4)
	, TIME_DIVISION(1000)
	, METEORITE_POP_CATEGORY(5)
	, SCORE_FONT_SIZE(130)
	, FONT_SIZE(80)
	, FONT_THICK(1)
	, GAME_FINISH_TIME(0)
	, WAVE1_POP_START_TIME(90)
	, WAVE2_POP_START_TIME(80)
	, WAVE3_POP_START_TIME(60)
	, WAVE4_POP_START_TIME(40)
	, WAVE5_POP_START_TIME(20)
	, WAVE1_POP_END_TIME(80)
	, WAVE2_POP_END_TIME(60)
	, WAVE3_POP_END_TIME(40)
	, WAVE4_POP_END_TIME(20)
	, WAVE5_POP_END_TIME(0)
	, WAVE1(1)
	, WAVE2(2)
	, WAVE3(3)
	, WAVE4(4)
	, WAVE5(5)
	, WAVE2_STOP_TIME(80)
	, WAVE3_STOP_TIME(60)
	, WAVE4_STOP_TIME(40)
	, WAVE5_STOP_TIME(20)
	, WAVE2_RELEASE_TIME(79)
	, WAVE3_RELEASE_TIME(59)
	, WAVE4_RELEASE_TIME(39)
	, WAVE5_RELEASE_TIME(19)
	, WAVE1_POP_COUNT(1.2f)
	, WAVE2_POP_COUNT(1.0f)
	, WAVE3_POP_COUNT(0.7f)
	, WAVE4_POP_COUNT(0.9f)
	, WAVE5_POP_COUNT(0.7f)
	, INITIAL_METEORITE_POP_COUNT(0.0f)
	, GAME_START_COUNT(3.0f)
	, FADE_START_COUNT(1.0f)
	, countDownStop(false)
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(scoreFont);
	DeleteFontToHandle(fontHandle);
}

/// <summary>
/// ����������
/// </summary>
void GameScene::Initialize()
{
	camera = new Camera();

	light = new Light(1);

	backGround = new BackGround();

	field = new Field();

	player = new Player();

	effectManager = new EffectManager();

	evaluation = new Evaluation();

	hitChecker = new HitChecker(effectManager, evaluation);

	uiManager = new UiManager();

	scoreEarn = new ScoreEarn();

	fadeManager = new FadeManager();

	resultUi = new ResultUi();

	//�t�H���g�̐���
	scoreFont = CreateFontToHandle("Oranienbaum", SCORE_FONT_SIZE, FONT_THICK);
	fontHandle = CreateFontToHandle("Oranienbaum", FONT_SIZE, FONT_THICK);

	pUpdate = &GameScene::UpdateStart;
}

/// <summary>
/// 覐΂�o�^
/// </summary>
/// <param name="newMeteorite">�o�^����覐΂̃|�C���^</param>
void GameScene::EntryMeteorite(Meteorite* newMeteorite)
{
	meteorite.emplace_back(newMeteorite);
}

/// <summary>
/// 覐΂��폜
/// </summary>
/// <param name="deleteMeteorite">�폜����覐΂̃|�C���^</param>
void GameScene::DeleteMeteorite(Meteorite* deleteMeteorite)
{
	//覐΃I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(meteorite.begin(), meteorite.end(), deleteMeteorite);

	if (iter != meteorite.end())
	{
		//覐΃I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, meteorite.end() - 1);
		meteorite.pop_back();

		return;
	}
}

/// <summary>
/// 覐΂̏o���Ԋu
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void GameScene::MeteoritePop(float deltaTime)
{
	meteoritePopCount += deltaTime;

	Pop pop[] =
	{
		{WAVE1_POP_START_TIME, WAVE1_POP_END_TIME, WAVE1_POP_COUNT, WAVE1},
		{WAVE2_POP_START_TIME, WAVE2_POP_END_TIME, WAVE2_POP_COUNT, WAVE2},
		{WAVE3_POP_START_TIME, WAVE3_POP_END_TIME, WAVE3_POP_COUNT, WAVE3},
		{WAVE4_POP_START_TIME, WAVE4_POP_END_TIME, WAVE4_POP_COUNT, WAVE4},
		{WAVE5_POP_START_TIME, WAVE5_POP_END_TIME, WAVE5_POP_COUNT, WAVE5},
	};

	for (int i = 0; i < METEORITE_POP_CATEGORY; i++)
	{
		if (countDown < pop[i].popStartTime && countDown > pop[i].popEndTime && meteoritePopCount > pop[i].popCount)
		{
			Meteorite* newMeteorite = new Meteorite(player);
			EntryMeteorite(newMeteorite);
			meteoritePopCount = INITIAL_METEORITE_POP_COUNT;
			wave = pop[i].wave;
		}
	}
}

/// <summary>
/// �Q�[�����Ԍv�Z
/// </summary>
void GameScene::GameCountDown()
{
	//���݂̎��Ԃ��擾
	nowTime = GetNowCount();

	if (!countDownStop)
	{
		countDown = gameTime - (nowTime - startTime) / TIME_DIVISION;
	}

	Time time[] =
	{
		{WAVE2_STOP_TIME, WAVE2_RELEASE_TIME},
		{WAVE3_STOP_TIME, WAVE3_RELEASE_TIME},
		{WAVE4_STOP_TIME, WAVE4_RELEASE_TIME},
		{WAVE5_STOP_TIME, WAVE5_RELEASE_TIME},
	};

	for (int i = 0; i < STOP_TIME_CATEGORY; i++)
	{
		//�������Ԃ��~�߂鎞�ԂɂȂ�����
		if (countDown == time[i].stopTime)
		{
			countDown = time[i].stopTime;
			countDownStop = true;

			//�E�F�[�u�摜�̓��ߏ������I�������
			if (uiManager->AlphaEnd())
			{
				//�Q�[���N�����̎��Ԃ��擾
				startTime = GetNowCount();

				//���ߏ����̏�����
				uiManager->AlphaReset();

				countDownStop = false;
				gameTime = time[i].releaseTime;
			}
		}
	}

	//�������Ԃ�0�ɂȂ�����
	if (countDown == GAME_FINISH_TIME)
	{
		gameState = GameState::FINISH;
		pUpdate = &GameScene::UpdateFinish;
	}
}

/// <summary>
/// �V�[���؂�ւ�
/// </summary>
void GameScene::SceneChange()
{
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		sceneChangeTitle = true;
	}

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		sceneChangeGame = true;
	}
}

/// <summary>
/// ��ʂ�J�ڂ���
/// </summary>
void GameScene::ReturnScreen()
{
	if (sceneChangeTitle)
	{
		fadeManager->FadeMove();

		//���U���gBGM���~
		SoundManager::GetInstance().StopBgm();

		//�t�F�[�h���I�������
		if (fadeManager->FadeEnd())
		{
			//�^�C�g����ʂ�
			nowSceneType = SceneType::TITLE;
		}
	}

	if (sceneChangeGame)
	{
		fadeManager->FadeMove();

		//���U���gBGM���~
		SoundManager::GetInstance().StopBgm();

		//�t�F�[�h���I�������
		if (fadeManager->FadeEnd())
		{
			//������x�v���C����
			gameState = GameState::START;
			Initialize();

			frame = 0.0f;

			sceneChangeGame = false;
		}
	}
}

/// <summary>
/// ���U���g��ʗp�X�R�A
/// </summary>
void GameScene::ResultScore()
{
	//�X�R�A���v�Z
	scoreEarn->Update();

	//�X�R�A���擾
	score = scoreEarn->GetScore();
	excellentCount = scoreEarn->GetExcellentCount();
	greatCount = scoreEarn->GetGreatCount();
	goodCount = scoreEarn->GetGoodCount();
	missCount = scoreEarn->GetMissCount();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
SceneType GameScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}

	return nowSceneType;
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void GameScene::UpdateStart(float deltaTime)
{
	frame += deltaTime;

	player->Update(deltaTime);

	//3�b�o�߂�����
	if (frame > GAME_START_COUNT)
	{
		//�Q�[���N�����̎��Ԃ��擾
		startTime = GetNowCount();

		//�Q�[��BGM���Đ�
		SoundManager::GetInstance().PlayBgm(SoundManager::GAME);

		gameState = GameState::GAME;
		pUpdate = &GameScene::UpdateGame;
	}
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void GameScene::UpdateGame(float deltaTime)
{
	backGround->Update();

	player->Update(deltaTime);

	//覐΂̏o���Ԋu
	MeteoritePop(deltaTime);
	
	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Update(deltaTime);

		if (wave == 5)
		{
			meteoritePtr->SpeedUp();
		}

		//覐΂ƏՓ˂����������͐������Ԃ�0�ɂȂ�����覐΂�����
		if (hitChecker->Hit() || countDown == GAME_FINISH_TIME)
		{
			DeleteMeteorite(meteoritePtr);
		}
	}

	hitChecker->PlayerAndMeteorite(player, &meteorite, scoreEarn);

	ResultScore();

	GameCountDown();
}

/// <summary>
/// �Q�[���I��
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void GameScene::UpdateFinish(float deltaTime)
{
	frame += deltaTime;

	//�Q�[��BGM���~
	SoundManager::GetInstance().StopBgm();

	TimeSlow::GetInstance().SetTimeSlow(false);

	//1�b�o�߂�����
	if (frame > FADE_START_COUNT)
	{
		fadeManager->FadeMove();
	}

	//�t�F�[�h���I�������
	if (fadeManager->FadeEnd())
	{
		gameState = GameState::RESULT;
		pUpdate = &GameScene::UpdateResult;

		fadeManager->FadeReset();
	}
}

/// <summary>
/// ���ʉ��
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void GameScene::UpdateResult(float deltaTime)
{
	backGround->Update();

	//���U���gBGM���Đ�
	SoundManager::GetInstance().PlayBgm(SoundManager::RESULT);

	//�ǂ̃V�[���ɂ��J�ڂ��Ă��Ȃ��Ȃ��
	if (!sceneChangeTitle && !sceneChangeGame)
	{
		SceneChange();
	}

	ReturnScreen();
}

/// <summary>
/// �`�揈��
/// </summary>
void GameScene::Draw()
{
	backGround->Draw();

	evaluation->Draw();

	if (gameState == GameState::GAME || gameState == GameState::FINISH)
	{
		field->Draw();

		player->Draw();

		for (auto meteoritePtr : meteorite)
		{
			meteoritePtr->Draw();
		}
	}

	effectManager->Draw();

	uiManager->Draw(gameState, frame, fontHandle, countDown, score, wave);

	if (gameState == GameState::RESULT)
	{
		resultUi->Draw(scoreFont, fontHandle, score, excellentCount, greatCount, goodCount, missCount);
	}

	if (gameState == GameState::FINISH || gameState == GameState::RESULT)
	{
		fadeManager->Draw();
	}
}