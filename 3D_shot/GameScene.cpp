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
	, meteorite()
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
	, pUpdate(nullptr)
	, GAME_TIME(5)
	, GAME_START_COUNT(3.0f)
	, FADE_START_COUNT(1.0f)
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

	light = new Light();
	light->GameLight();

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
	scoreFont = CreateFontToHandle("Oranienbaum", 130, 1);
	fontHandle = CreateFontToHandle("Oranienbaum", 80, 1);

	//�Q�[��BGM���Đ�
	SoundManager::GetInstance().PlayBgm(SoundManager::GAME);

	pUpdate = &GameScene::UpdateStart;
}

/// <summary>
/// 覐΂�o�^
/// </summary>
/// <param name="newMeteorite"></param>
void GameScene::EntryMeteorite(Meteorite* newMeteorite)
{
	meteorite.emplace_back(newMeteorite);
}

/// <summary>
/// 覐΂��폜
/// </summary>
/// <param name="deleteMeteorite"></param>
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
/// <param name="deltaTime"></param>
void GameScene::MeteoritePop(float deltaTime)
{
	meteoritePopCount += deltaTime;

	if (countDown > 80 && meteoritePopCount > 1.2f)
	{
		Meteorite* newMeteorite = new Meteorite(player);
		EntryMeteorite(newMeteorite);
		meteoritePopCount = 0.0f;
		wave = 1;
	}

	if (countDown < 80 && countDown > 60 && meteoritePopCount > 1.0f)
	{
		Meteorite* newMeteorite = new Meteorite(player);
		EntryMeteorite(newMeteorite);
		meteoritePopCount = 0.0f;
		wave = 2;
	}

	if (countDown < 60 && countDown > 40 && meteoritePopCount > 0.7f)
	{
		Meteorite* newMeteorite = new Meteorite(player);
		EntryMeteorite(newMeteorite);
		meteoritePopCount = 0.0f;
		wave = 3;
	}

	if (countDown < 40 && countDown > 20 && meteoritePopCount > 0.9f)
	{
		Meteorite* newMeteorite = new Meteorite(player);
		EntryMeteorite(newMeteorite);
		meteoritePopCount = 0.0f;
		wave = 4;
	}

	if (countDown < 20 && meteoritePopCount > 0.7f)
	{
		Meteorite* newMeteorite = new Meteorite(player);
		EntryMeteorite(newMeteorite);
		meteoritePopCount = 0.0f;
		wave = 5;
	}
}

/// <summary>
/// �Q�[�����Ԍv�Z
/// </summary>
void GameScene::GameCountDown()
{
	nowTime = GetNowCount();
	countDown = GAME_TIME - (nowTime - startTime) / 1000;

	//�������Ԃ�0�ɂȂ�����
	if (countDown == 0)
	{
		gameState = GameState::FINISH;
		pUpdate = &GameScene::UpdateFinish;
	}
}

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
/// <param name="deltaTime"></param>
SceneType GameScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V

		return nowSceneType;
	}
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateStart(float deltaTime)
{
	frame += deltaTime;

	player->Update(deltaTime);

	//3�b�o�߂�����
	if (frame > GAME_START_COUNT)
	{
		//�Q�[���N�����̎��Ԃ��擾
		startTime = GetNowCount();

		gameState = GameState::GAME;
		pUpdate = &GameScene::UpdateGame;
	}
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
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
		if (hitChecker->Hit() || countDown == 0)
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
/// <param name="deltaTime"></param>
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
/// <param name="deltaTime"></param>
void GameScene::UpdateResult(float deltaTime)
{
	backGround->Update();

	//���U���gBGM���Đ�
	SoundManager::GetInstance().PlayBgm(SoundManager::RESULT);

	if (CheckHitKey(KEY_INPUT_BACK))
	{
		sceneChangeTitle = true;
	}

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

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		gameState = GameState::START;
		Initialize();
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void GameScene::Draw()
{
	backGround->Draw();

	if (gameState != GameState::RESULT && gameState != GameState::START)
	{
		evaluation->Draw();

		field->Draw();

		player->Draw();

		for (auto meteoritePtr : meteorite)
		{
			meteoritePtr->Draw();
		}

		effectManager->Draw();
	}

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