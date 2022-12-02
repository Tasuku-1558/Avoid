#include "PlayScene.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "Common.h"
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

const int PlayScene::GAMETIME = 10;		//�Q�[������

PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, frame(0)
		, camera(nullptr)
		, light(nullptr)
		, background(nullptr)
		, field(nullptr)
		, hitChecker(nullptr)
		, uiManager()
		, player(nullptr)
		, explosion(nullptr)
		, evaluation(nullptr)
		, scoreearn(nullptr)
		, pUpdate(nullptr)
		, meteorite()
		, startTime(0)
		, nowTime(0)
		, countDown(0)
		, score(0)
		, font(0)
		, targetScore(0)
		, slow(false)
		, meteoritePopCount(150.0f)
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
	background = new BackGround();
	background->Initialize();

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
	scoreearn = new ScoreEarn();
}

//�I������
void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(player);
	player->Finalize();

	for (auto ptr : meteorite)
	{
		SafeDelete(ptr);
		ptr->Finalize();
	}
	
	SafeDelete(background);
	background->Finalize();

	SafeDelete(field);
	field->Finalize();

	SafeDelete(hitChecker);

	SafeDelete(uiManager);
	uiManager->Finalize();
	
	SafeDelete(explosion);
	explosion->Finalize();

	SafeDelete(evaluation);
	evaluation->Finalize();

	SafeDelete(scoreearn);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

void PlayScene::Activate()
{
	state = START;
	frame = 0;

	font = CreateFontToHandle("Oranienbaum", 80, 1);
	
	pUpdate = &PlayScene::UpdateStart;
	
	for (auto ptr : meteorite)
	{
		//覐Ώ�����
		ptr->Initialize();

		//覐Ί�����
		ptr->Activate();
	}
	
	background->Activate();

	field->Activate();

	evaluation->Activate();

	explosion->Activate();
	
	player->Activate();
}

//�Q�[�����Ԍv�Z
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

//覐΂�o�^
void PlayScene::EntryMeteorite(Meteorite* newMeteorite)
{
	meteorite.emplace_back(newMeteorite);
}

//覐΂��폜
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

void PlayScene::MeteoritePop(float deltaTime)
{
	meteoritePopCount += deltaTime;

	if (countDown > 11)
	{
		if (meteoritePopCount > 1.2f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0;
		}
	}
	/*if (countDown < 29)
	{
		if (meteoritePopCount > 0.9f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0;
		}
	}*/
	if (countDown < 10)
	{
		if (meteoritePopCount > 0.5f)
		{
			Meteorite* newMeteorite = new Meteorite;
			EntryMeteorite(newMeteorite);
			meteoritePopCount = 0;
		}
	}
}

void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}

	++frame;
}

//�Q�[���J�n�O
void PlayScene::UpdateStart(float deltaTime)
{
	//if (frame > 10)
	{
		frame = 0;
		score = 0;
		state = GAME;
		
		Score::GetInstance().Activate();

		scoreearn->Activate();

		TimeSlow::GetInstance().SetTimeSlow(slow);
		
		pUpdate = &PlayScene::UpdateGame;

		for (auto ptr : meteorite)
		{
			//覐Ί�����
			ptr->Activate();
		}
		
		//�Q�[���N�����̎��Ԃ��擾
		startTime = GetNowCount();
	}
}

//�Q�[����
void PlayScene::UpdateGame(float deltaTime)
{
	//�v���C���[�̐���
	player->Update(deltaTime);

	//覐΂̏o���Ԋu
	MeteoritePop(deltaTime);
	
	for (auto ptr : meteorite)
	{
		//覐ΐ���
		ptr->Update(deltaTime, player);

		//�������Ԃ�10�b�ȉ��ɂȂ�����t�B�[�o�[��Ԃֈڍs
		if (countDown < 10)
		{
			state = FEVER;
			ptr->SpeedUp();
			pUpdate = &PlayScene::UpdateFever;
		}

		//�v���C���[��覐΂̓����蔻��
		hitChecker->PlayerAndMeteorite(player, ptr, explosion, evaluation, scoreearn);

		//覐΂ƏՓ˂����������͐������Ԃ�0�ɂȂ�����
		if (hitChecker->Hit())
		{
			DeleteMeteorite(ptr);
		}
		else if (countDown == 0)
		{
			DeleteMeteorite(ptr);
		}
	}

	//�X�R�A���v�Z
	Score::GetInstance().Scoring();

	//�X�R�A���擾
	score = Score::GetInstance().GetScore();

	GameCountDown();
}

//�t�B�[�o�[��
void PlayScene::UpdateFever(float deltaTime)
{
	UpdateGame(deltaTime);
}

void PlayScene::Draw()
{
	//�w�i�`��
	background->Draw();

	//�]��UI�̕`��
	evaluation->Draw();

	//�v���C���[�`��
	player->Draw();

	for (auto ptr : meteorite)
	{
		//覐Ε`��
		ptr->Draw();
	}

	//�t�B�[���h�`��
	field->Draw();

	//�����G�t�F�N�g�`��
	explosion->Draw();

	//UI�Ǘ��N���X�̕`��
	uiManager->Draw(state, frame);

	//�������ԕ\��
	DrawFormatStringToHandle(500, 100, GetColor(255, 0, 0), font, "TIME : %d", countDown);

	//�l���X�R�A�\��
	DrawFormatStringToHandle(1000, 100, GetColor(255, 255, 0), font, "SCORE : %d", score);
}