#include "PlayScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Common.h"
#include "Player.h"
#include "Meteorite.h"
#include "MeteoriteManager.h"
#include "Camera.h"
#include "BackGround.h"
#include "HitChecker.h"
#include "Evaluation.h"
#include "EarnScore.h"
#include "Explosion.h"


const int PlayScene::GAMETIME = 5;		//�Q�[������

PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, frame(0)
		, camera(nullptr)
		, background(nullptr)
		, hitchecker(nullptr)
		, player(nullptr)
		, explosion(nullptr)
		, evaluation(nullptr)
		, earnscore(nullptr)
		, pUpdate(nullptr)
		, meteoriteManager(nullptr)
		, meteorite()
		, meteoritePopFlag(false)
		, startTime(0)
		, nowTime(0)
		, countDown(0)
		, score(0)
		, targetScore(0)
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

	//�����蔻��N���X
	hitchecker = new HitChecker();

	//�����G�t�F�N�g�N���X
	explosion = new Explosion();
	explosion->Initialize();

	//�]��UI�N���X
	evaluation = new Evaluation();
	evaluation->Initialize();

	//�X�R�A�N���X
	earnscore = new EarnScore();
	
	//MeteoriteManager::Initialize();
}

void PlayScene::Finalize()
{
	//�J�����N���X�����
	SafeDelete(camera);

	//�v���C���[�N���X�����
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
	
	//覐΃}�l�[�W���[�����
	//MeteoriteManager::Finalize();
	
	//�w�i�N���X
	SafeDelete(background);
	background->Finalize();

	//�q�b�g�`�F�b�J�[�N���X�����
	SafeDelete(hitchecker);
	
	//�����G�t�F�N�g�N���X�����
	SafeDelete(explosion);
	explosion->Finalize();

	//�]��UI�N���X�����
	SafeDelete(evaluation);
	evaluation->Finalize();

	//�X�R�A�N���X�����
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
	
	
	//Meteorite* me = new Meteorite;

	////覐Ί�����
	//me->Activate();
	//MeteoriteManager::Entry(me);

	background->Activate();

	earnscore->Activate();

	//�v���C���[������
	player->Activate();

	//�Q�[���N�����̎��Ԃ��擾
	startTime = GetNowCount();
}


void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		//��Ԃ��ƂɍX�V
	}

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

				//�v���C���[��覐΂̓����蔻��
				hitchecker->PlayerAndMeteorite(player, /*ptr*/meteorite, meteoriteManager, explosion, evaluation, earnscore);
			}
		}
	}

	++frame;
}

void PlayScene::UpdateStart()
{
	/*if (frame > 60)
	{*/
		frame = 0;
		state = GAME;
		pUpdate = &PlayScene::UpdateGame;
	/*}*/
	
}

void PlayScene::UpdateGame()
{
	//HitChecker�̃X�R�A���擾
	targetScore = earnscore->GetScore();

	//�X�R�A��ڕW�X�R�A�ɑ����������鏈��
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

	//�������Ԃ�0�ɂȂ�����
	if (countDown == 0)
	{
		parent->SetNextScene(SceneManager::RESULT);
		return;
	}
}

void PlayScene::Draw()
{
	//�v���C���[�`��
	player->Draw();

	//�w�i�`��
	background->Draw();

	//�����G�t�F�N�g�`��
	explosion->Draw();

	//�]��UI�̕`��
	evaluation->Draw();

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//覐Ε`��
			meteorite[i]->Draw();
		}
	}

	//覐΃}�l�[�W���[�`��
	//MeteoriteManager::Draw();


	SetFontSize(80);			//�����̃t�H���g�T�C�Y�ύX
	ChangeFont("�l�r ����");	//��ނ�MS�����ɕύX

	//�������ԕ\��
	DrawFormatString(500, 100, GetColor(255, 0, 0), "TIME : %d", countDown);

	//�l���X�R�A�\��
	DrawFormatString(1000, 100, GetColor(255, 255, 0), "SCORE : %d", score);
}