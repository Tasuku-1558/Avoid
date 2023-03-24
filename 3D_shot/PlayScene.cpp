#include "PlayScene.h"

#include "PreCompiledHeader.h"
#include "Player.h"
#include "Meteorite.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Field.h"
#include "HitChecker.h"
#include "UiManager.h"
#include "Evaluation.h"
#include "ScoreEarn.h"
#include "EffectManager.h"
#include "Score.h"
#include "TimeSlow.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayScene::PlayScene()
	: SceneBase(SceneType::PLAY)
	, gameState(GameState::START)
	, frame(0.0f)
	, pUpdate(nullptr)
	, meteorite()
	, startTime(0)
	, nowTime(0)
	, countDown(0)
	, score(0)
	, font(0)
	, targetScore(0)
	, slow(false)
	, meteoritePopCount(0.0f)
	, wave(0)
	, GAME_TIME(90)
{
	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{
	for (auto meteoritePtr : meteorite)
	{
		DeleteMeteorite(meteoritePtr);
	}

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

/// <summary>
/// ����������
/// </summary>
void PlayScene::Initialize()
{
	camera = new Camera();

	light = new Light();

	player = new Player();

	backGround = new BackGround();

	field = new Field();

	effectManager = new EffectManager();

	hitChecker = new HitChecker(effectManager);

	uiManager = new UiManager();

	evaluation = new Evaluation();

	scoreEarn = new ScoreEarn();
}

/// <summary>
/// ����������
/// </summary>
void PlayScene::Activate()
{
	pUpdate = &PlayScene::UpdateStart;

	font = CreateFontToHandle("Oranienbaum", 80, 1);
}

/// <summary>
/// �Q�[�����Ԍv�Z
/// </summary>
void PlayScene::GameCountDown()
{
	nowTime = GetNowCount();
	countDown = GAME_TIME - (nowTime - startTime) / 1000;

	//�������Ԃ�0�ɂȂ�����
	//���ʉ�ʂ֑J�ڂ���
	if (countDown == 0)
	{
		nowSceneType = SceneType::RESULT;
	}
}

/// <summary>
/// 覐΂�o�^
/// </summary>
/// <param name="newMeteorite"></param>
void PlayScene::EntryMeteorite(Meteorite* newMeteorite)
{
	meteorite.emplace_back(newMeteorite);
}

/// <summary>
/// 覐΂��폜
/// </summary>
/// <param name="deleteMeteorite"></param>
void PlayScene::DeleteMeteorite(Meteorite* deleteMeteorite)
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
void PlayScene::MeteoritePop(float deltaTime)
{
	meteoritePopCount += deltaTime;

	if (countDown > 70)
	{
		if (meteoritePopCount > 1.2f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			wave = 1;
		}
	}
	if (countDown < 70)
	{
		if (meteoritePopCount > 0.8f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			wave = 2;
		}
	}
	if (countDown < 50)
	{
		if (meteoritePopCount > 0.5f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			wave = 3;
		}
	}
	if (countDown < 20)
	{
		if (meteoritePopCount > 1.0f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			
		}
	}
	if (countDown < 10)
	{
		if (meteoritePopCount > 1.0f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0.0f;
			
		}
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
SceneType PlayScene::Update(float deltaTime)
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
void PlayScene::UpdateStart(float deltaTime)
{
	gameState = GameState::GAME;
	pUpdate = &PlayScene::UpdateWave1;

	Score::GetInstance().Activate();

	TimeSlow::GetInstance().SetTimeSlow(slow);

	//�Q�[���N�����̎��Ԃ��擾
	startTime = GetNowCount();
}

/// <summary>
/// Wave1
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateWave1(float deltaTime)
{
	backGround->Update();

	player->Update(deltaTime);

	//覐΂̏o���Ԋu
	MeteoritePop(deltaTime);
	
	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Update(deltaTime, player);

		//�������Ԃɂ����覐΂̐F��X�s�[�h���ω�
		if (countDown < 50)
		{
			meteoritePtr->ChangeColor(0.0f, 1.0f, 1.0f);
		}
		if (countDown < 20)
		{
			meteoritePtr->ChangeColor(50.0f, 50.0f, 0.0f);
			wave = 4;
		}
		if (countDown < 11)		//�������Ԃ�11�b�ȉ��ɂȂ�����t�B�[�o�[��Ԃֈڍs
		{
			gameState = GameState::FINALWAVE;
			meteoritePtr->SpeedUp();
			meteoritePtr->ChangeColor(5.0f, 0.0f, 0.0f);
			wave = 5;
			pUpdate = &PlayScene::UpdateFinal;
		}

		//覐΂ƏՓ˂����������͐������Ԃ�0�ɂȂ�����覐΂�����
		if (hitChecker->Hit() || countDown == 0)
		{
			DeleteMeteorite(meteoritePtr);
		}
	}

	//�v���C���[��覐΂̓����蔻��
	hitChecker->PlayerAndMeteorite(player, &meteorite, evaluation, scoreEarn);

	//�X�R�A���擾
	score = Score::GetInstance().GetScore();

	//�X�R�A���v�Z
	Score::GetInstance().Scoring();

	GameCountDown();
}

/// <summary>
/// �t�B�[�o�[��
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateFinal(float deltaTime)
{
	UpdateWave1(deltaTime);
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayScene::Draw()
{
	backGround->Draw();

	evaluation->Draw();

	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Draw();
	}

	field->Draw();

	player->Draw();

	effectManager->Draw();

	uiManager->Draw(gameState, font, countDown, score, wave);
}