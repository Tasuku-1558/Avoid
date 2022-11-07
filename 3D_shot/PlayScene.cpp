#include "PlayScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Common.h"
#include "Player.h"
#include "Meteorite.h"
#include "MeteoriteManager.h"
#include "Camera.h"
#include "BackGround.h"
#include "Field.h"
#include "HitChecker.h"
#include "UiManager.h"
#include "Evaluation.h"
#include "EarnScore.h"
#include "Explosion.h"
#include "Score.h"

const int PlayScene::GAMETIME = 30;		//�Q�[������

PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, frame(0)
		, camera(nullptr)
		, background(nullptr)
		, field(nullptr)
		, hitChecker(nullptr)
		, uiManager(nullptr)
		, player(nullptr)
		, explosion(nullptr)
		, evaluation(nullptr)
		, earnscore(nullptr)
		, pUpdate(nullptr)
		, meteorite()
		, meteoritePopFlag(false)
		, startTime(0)
		, nowTime(0)
		, countDown(0)
		, score(0)
		, targetScore(0)
		, feverGauge(0.0f)
		, count(0)
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
	earnscore = new EarnScore();
}

void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(player);
	player->Finalize();

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//覐΃N���X�����
			SafeDelete(meteorite[i]);
			meteorite[i]->Finalize();
		}
	}
	
	//for (auto ptr : meteorite)
	//{
	//	//覐΃}�l�[�W���[�����
	//	MeteoriteManager::Finalize();
	//}
	
	
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

	SafeDelete(earnscore);
}

void PlayScene::Activate()
{
	state = START;
	frame = 0;
	
	pUpdate = &PlayScene::UpdateStart;

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		//覐ΐ���
		meteorite[i] = new Meteorite();

		if (meteorite[i] != nullptr)
		{
			//覐Ώ�����
			meteorite[i]->Initialize();

			//覐Ί�����
			meteorite[i]->Activate();
		}
	}

	//for (auto ptr : meteorite)
	//{
	//	Meteorite* me = new Meteorite;

	//	//覐Ί�����
	//	me->Activate();
	//	MeteoriteManager::Entry(me);
	//}
	
	background->Activate();

	field->Activate();

	//�v���C���[������
	player->Activate();
}

void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}

	++frame;
}

void PlayScene::UpdateStart(float deltaTime)
{
	/*if (frame > 60)
	{*/
		frame = 0;
		feverGauge = 0.0f;
		state = GAME;
		
		earnscore->Activate();
		Score::GetInstance().Activate();

		pUpdate = &PlayScene::UpdateGame;
		
		
		//�Q�[���N�����̎��Ԃ��擾
		startTime = GetNowCount();
	/*}*/
	
}

void PlayScene::UpdateGame(float deltaTime)
{
	//�v���C���[�̐���
	player->Update(deltaTime);

	meteoritePopFlag = true;

	for (/*auto ptr:meteorite*/int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//覐Ώo���t���O��true�̎�
			if (meteoritePopFlag)
			{
				meteoritePopFlag = false;
				
				//覐ΐ���
				meteorite[i]->Update(deltaTime, player);


				//覐΃}�l�[�W���[����
				//MeteoriteManager::Update(deltaTime, player);

				//MeteoriteManager::PlayerAndMeteorite(player, ptr, explosion, evaluation, earnscore);

				//�v���C���[��覐΂̓����蔻��
				hitChecker->PlayerAndMeteorite(player, meteorite, explosion, evaluation, earnscore);
			}
		}
	}

	feverGauge = Score::GetInstance().GetScore() / static_cast<float>(50);
	if (feverGauge > 70.0f)
	{
		feverGauge = 0.0f;
		pUpdate = &PlayScene::UpdateFever;
	}
	
	//earnscore�̃X�R�A���擾
	targetScore = Score::GetInstance().GetScore();

	//�X�R�A��ڕW�X�R�A�ɑ�������
	if (targetScore != score)
	{
		if (targetScore > score)
		{
			score += 100;
		}
		else
		{
			score -= 100;
		}
	}

	nowTime = GetNowCount();
	countDown = GAMETIME - (nowTime - startTime) / 1000;

	//TIME��0�ɂȂ�����
	if (countDown == 0)
	{
		parent->SetNextScene(SceneManager::RESULT);
		return;
	}
}

void PlayScene::UpdateFever(float deltaTime)
{
	UpdateGame(deltaTime);
}

void PlayScene::Draw()
{
	//�v���C���[�`��
	player->Draw();

	field->Draw();

	//�w�i�`��
	background->Draw();

	//�����G�t�F�N�g�`��
	explosion->Draw();

	//�]��UI�̕`��
	evaluation->Draw();

	//UI�Ǘ��N���X�̕`��
	uiManager->Draw(state, frame, feverGauge);

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//覐Ε`��
			meteorite[i]->Draw();
		}
	}

	//for (auto ptr : meteorite)
	//{
	//	//覐΃}�l�[�W���[�`��
	//	MeteoriteManager::Draw();
	//}

	SetFontSize(80);			//�����̃t�H���g�T�C�Y�ύX

	//�������ԕ\��
	DrawFormatString(500, 100, GetColor(255, 0, 0), "TIME : %d", countDown);

	//�l���X�R�A�\��
	DrawFormatString(1000, 100, GetColor(255, 255, 0), "SCORE : %d", score);
}