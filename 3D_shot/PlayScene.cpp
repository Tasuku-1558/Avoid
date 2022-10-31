#include "PlayScene.h"
#include "DxLib.h"
#include "Common.h"
#include "Camera.h"
#include "Player.h"
#include "Meteorite.h"
#include "MeteoriteManager.h"
#include "HitChecker.h"
#include "Evaluation.h"
#include "Explosion.h"
#include "SceneManager.h"


//�f�o�b�N�p
//#define LINE_AREA_SIZE		10000.0f	// ���C����`���͈�
//#define LINE_NUM			50			// ���C���̐�

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
		, gameBackGround(0)
		, score(0)
		, targetScore(0)
{
}

PlayScene::~PlayScene()
{
	//�����Ȃ�
}

void PlayScene::Initialize()
{
	//�Q�[���w�i
	gameBackGround = LoadGraph("data/image/GameBackground.png");

	camera = new Camera();

	player = new Player();

	hitchecker = new HitChecker();

	explosion = new Explosion();

	evaluation = new Evaluation();

	//覐΃}�l�[�W���[������
	//MeteoriteManager::Initialize();

	//�v���C���[������
	player->Initialize();

	//�����G�t�F�N�g������
	explosion->Initialize();

	//�J����������
	camera->Initialize();

	//�]��UI������
	evaluation->Initialize();
}

void PlayScene::Finalize()
{
	//�Q�[���w�i�����
	DeleteGraph(gameBackGround);

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
	
	//�����G�t�F�N�g�����
	SafeDelete(explosion);
	explosion->Finalize();

	//�]��UI�����
	SafeDelete(evaluation);
	evaluation->Finalize();
}

void PlayScene::Activate()
{
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
	/*x = player->GetPosition().x;
	y = player->GetPosition().y;
	Direction = hitchecker->GetDirection();*/

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
	//�Q�[���w�i�`��
	DrawBillboard3D(VGet(0.0f, 300.0f, 1200.0f), 0.5f, 0.5f, 4000.0f, 0.0f, gameBackGround, TRUE);

	//�v���C���[�`��
	player->Draw();

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
	
	
	//�f�o�b�N�p
	/*{
		int i;
		VECTOR Pos1;
		VECTOR Pos2;

		SetUseZBufferFlag(TRUE);

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
		for (i = 0; i <= LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.x += LINE_AREA_SIZE / LINE_NUM;
			Pos2.x += LINE_AREA_SIZE / LINE_NUM;
		}

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		for (i = 0; i < LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.z += LINE_AREA_SIZE / LINE_NUM;
			Pos2.z += LINE_AREA_SIZE / LINE_NUM;
		}

		SetUseZBufferFlag(FALSE);
	}*/


	SetFontSize(80);			//�����̃t�H���g�T�C�Y�ύX
	ChangeFont("�l�r ����");	//��ނ�MS�����ɕύX

	//�������ԕ\��
	DrawFormatString(500, 100, GetColor(255, 0, 0), "TIME : %d", countDown);

	//�l���X�R�A�\��
	DrawFormatString(1000, 100, GetColor(255, 255, 0), "SCORE : %d", score);

	////�f�o�b�N�p
	//DrawFormatString(500, 300, GetColor(255, 0, 0), "x : %d", x);
	//DrawFormatString(500, 350, GetColor(255, 0, 0), "y : %d", y);
	//DrawFormatString(500, 400, GetColor(255, 0, 0), "Direction : %f", Direction);
}