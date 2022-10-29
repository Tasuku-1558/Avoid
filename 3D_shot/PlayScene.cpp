#include "PlayScene.h"
#include "Common.h"
#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
#include "Meteorite.h"
#include "MeteoriteManager.h"
#include "HitChecker.h"
#include "Evaluation.h"
#include "Explosion.h"
#include "SceneManager.h"


const int PlayScene::GAMETIME = 60;		//�Q�[������

PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, camera(nullptr)
		, hitchecker(nullptr)
		, player(nullptr)
		, explosion(nullptr)
		, evaluation(nullptr)
		, meteorite()
		, meteoritePopFlag(false)
		, startTime(0)
		, nowTime(0)
		, countDown(0)
		, gameBackground(0)
		, score(0)
		, targetScore(0)
{
	//�����Ȃ�
}

PlayScene::~PlayScene()
{
	//�����Ȃ�
}

void PlayScene::Initialize()
{
	//�Q�[����ʔw�i
	gameBackground = LoadGraph("data/Image/GameBackground.png");

	camera = new Camera();

	player = new Player();

	hitchecker = new HitChecker();

	explosion = new Explosion();

	evaluation = new Evaluation();

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		//覐ΐ���
		meteorite[i] = new Meteorite();

		if (meteorite[i] != nullptr)
		{
			//覐Ώ�����
			meteorite[i]->Initialize();
		}
	}
	
	//覐΃}�l�[�W���[������
	//MeteoriteManager::Initialize();

	//�v���C���[������
	player->Initialize();

	//�G�t�F�N�g������
	explosion->Initialize();

	//�J����������
	camera->Initialize();

	//�]��UI������
	evaluation->Initialize();
}

void PlayScene::Finalize()
{
	//�Q�[����ʔw�i�����
	DeleteGraph(gameBackground);

	//�J���������
	SafeDelete(camera);

	//�v���C���[�����
	SafeDelete(player);

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//覐΂����
			SafeDelete(meteorite[i]);
		
		}
	}

	//覐΃}�l�[�W���[�����
	//MeteoriteManager::Finalize();
	
	//�q�b�g�`�F�b�J�[�����
	SafeDelete(hitchecker);
	
	SafeDelete(explosion);

	//�]��UI�̉��
	SafeDelete(evaluation);
}

void PlayScene::Activate()
{
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//覐Ί�����
			meteorite[i]->Activate();
		}
		
	}
	
	//for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	//{
	//	Meteorite* me = new Meteorite;

	//	//覐Ί�����
	//	me->Activate();
	//	MeteoriteManager::Entry(me);
	//}
	

	//�v���C���[������
	player->Activate();

	//�Q�[���N�����̎��Ԃ��擾
	startTime = GetNowCount();

	hitchecker->Initialize();
}


void PlayScene::Update(float deltaTime)
{
	//�v���C���[�̐���
	player->Update(deltaTime);

	meteoritePopFlag = true;
	
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//覐Ώo���t���O��true�̎�
			if (meteoritePopFlag)
			{
				meteoritePopFlag = false;
				
				
				//覐ΐ���
				meteorite[i]->Update(deltaTime, player);
				
				////覐΃}�l�[�W���[����
				//MeteoriteManager::Update(deltaTime, player);

				//�v���C���[��覐΂̓����蔻��
				hitchecker->PlayerAndMeteorite(player, meteorite, meteoriteManager, explosion, evaluation);

			}
		}
	}
	

	//�f�o�b�N�p
	x = player->GetPosition().x;
	y = player->GetPosition().y;
	Direction = hitchecker->GetDirection();

	//HitChecker�̃X�R�A���擾
	targetScore = hitchecker->GetScore();

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
	//�Q�[����ʔw�i�`��
	DrawBillboard3D(VGet(0.0f, 300.0f, 1200.0f), 0.5f, 0.5f, 4000.0f, 0.0f, gameBackground, TRUE);

	//�v���C���[�`��
	player->Draw();

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
	
	SetFontSize(60);			//�����̃t�H���g�T�C�Y�ύX
	ChangeFont("�l�r ����");	//��ނ�MS�����ɕύX

	//�������ԕ\��
	DrawFormatString(800, 100, GetColor(255, 0, 0), "TIME : %d", countDown);

	//�l���X�R�A�\��
	DrawFormatString(800, 150, GetColor(255, 255, 0), "SCORE : %d", score);

	//�f�o�b�N�p
	DrawFormatString(500, 300, GetColor(255, 0, 0), "x : %d", x);
	DrawFormatString(500, 350, GetColor(255, 0, 0), "y : %d", y);
	DrawFormatString(500, 400, GetColor(255, 0, 0), "Direction : %f", Direction);
}