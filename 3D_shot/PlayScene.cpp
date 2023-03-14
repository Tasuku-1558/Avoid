#include "PlayScene.h"
#include "DxLib.h"

#include "SceneManager.h"
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
#include "Explosion.h"
#include "Score.h"
#include "TimeSlow.h"

const int PlayScene::GAMETIME = 90;		//�Q�[������

PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, frame(0.0f)
		, camera(nullptr)
		, light(nullptr)
		, backGround(nullptr)
		, field(nullptr)
		, hitChecker(nullptr)
		, uiManager()
		, player(nullptr)
		, explosion(nullptr)
		, evaluation(nullptr)
		, scorEearn(nullptr)
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
{
	//�����Ȃ�
}

PlayScene::~PlayScene()
{
	//�����Ȃ�
}

//����������
void PlayScene::Initialize()
{
	//�J�����N���X
	camera = new Camera();
	camera->Initialize();

	//���C�g�N���X
	light = new Light();
	light->Initialize();

	//�v���C���[�N���X
	player = new Player();
	player->Initialize();

	//�w�i�N���X
	backGround = new BackGround();
	backGround->Initialize();

	//�t�B�[���h�N���X
	field = new Field();
	field->Initialize();

	//�����蔻��N���X
	hitChecker = new HitChecker();

	//UI�摜�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	//�����G�t�F�N�g�N���X
	explosion = new Explosion();
	explosion->Initialize();

	//�]��UI�N���X
	evaluation = new Evaluation();
	evaluation->Initialize();

	//�X�R�A�l���N���X
	scorEearn = new ScoreEarn();
}

//�I������
void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(player);

	for (auto meteoritePtr : meteorite)
	{
		SafeDelete(meteoritePtr);
	}
	
	SafeDelete(backGround);

	SafeDelete(field);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);
	
	SafeDelete(explosion);

	SafeDelete(evaluation);

	SafeDelete(scorEearn);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

void PlayScene::Activate()
{
	state = State::START;
	pUpdate = &PlayScene::UpdateStart;

	frame = 0.0f;
	wave = 0;
	countDown = 0;

	font = CreateFontToHandle("Oranienbaum", 80, 1);
	
	backGround->Activate();

	field->Activate();

	evaluation->Activate();

	explosion->Activate();
	
	player->Activate();
}

/// <summary>
/// �Q�[�����Ԍv�Z
/// </summary>
void PlayScene::GameCountDown()
{
	nowTime = GetNowCount();
	countDown = GAMETIME - (nowTime - startTime) / 1000;

	//�������Ԃ�0�ɂȂ�����
	if (countDown == 0)
	{
		parent->SetNextScene(SceneManager::RESULT);
		return;
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
void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateStart(float deltaTime)
{
	state = State::GAME;
	pUpdate = &PlayScene::UpdateGame;

	Score::GetInstance().Activate();

	scorEearn->Activate();

	TimeSlow::GetInstance().SetTimeSlow(slow);

	for (auto meteoritePtr : meteorite)
	{
		//覐Ί�����
		meteoritePtr->Activate();
	}

	//�Q�[���N�����̎��Ԃ��擾
	startTime = GetNowCount();
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateGame(float deltaTime)
{
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
			state = State::FINALWAVE;
			meteoritePtr->SpeedUp();
			meteoritePtr->ChangeColor(5.0f, 0.0f, 0.0f);
			wave = 5;
			pUpdate = &PlayScene::UpdateFever;
		}

		//�v���C���[��覐΂̓����蔻��
		hitChecker->PlayerAndMeteorite(player, meteoritePtr, explosion, evaluation, scorEearn);

		//覐΂ƏՓ˂����������͐������Ԃ�0�ɂȂ�����覐΂�����
		if (hitChecker->Hit() || countDown == 0)
		{
			DeleteMeteorite(meteoritePtr);
		}
	}

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
void PlayScene::UpdateFever(float deltaTime)
{
	UpdateGame(deltaTime);
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayScene::Draw()
{
	backGround->Draw();

	evaluation->Draw();

	player->Draw();

	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Draw();
	}

	field->Draw();

	explosion->Draw();

	uiManager->Draw(state, frame, font, countDown, score, wave);
}