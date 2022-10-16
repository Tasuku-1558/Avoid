#include "PlayScene.h"
#include "DxLib.h"
#include "Player.h"
#include "Meteorite.h"
#include "Camera.h"
#include "HitChecker.h"
#include "Utility.h"

const int PlayScene::GameTime = 60;		//�Q�[������

PlayScene::PlayScene():SceneBase(SceneType::PLAY)
		, camera(new Camera())
		, player(new Player())
		, hitchecker(new HitChecker())
		, MeteoritePopFlag(false)
		, StartTime(0)
		, NowTime(0)
		, CountDown(0)
		, GameBackground(0)
		, Score(0)
		, TargetScore(0)
{
	//覐΂̐���
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		meteorite[i] = new Meteorite();
	}

	//�v���C���[������
	player->Initialize();

	//覐Ώ�����
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			meteorite[i]->Initialize();
		}
	}

	//�Q�[���N�����̎��Ԃ��擾
	StartTime = GetNowCount();
}

PlayScene::~PlayScene()
{
	//�J���������
	SAFE_DELETE(camera);

	//�v���C���[�����
	SAFE_DELETE(player);

	//HitChecker�����
	SAFE_DELETE(hitchecker);

	//覐΂����
	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			SAFE_DELETE(meteorite[i]);
		}
	}

	//�Q�[����ʔw�i�����
	DeleteGraph(GameBackground);
}

void PlayScene::Initialize()
{
	////覐΃N���X�̃|�C���^���m�ۂ��邽�߂̔z��쐬
	//Meteorite* meteorite[Meteorite::METEORITE_ARRAY_NUMBER] = { nullptr };

	//�Q�[����ʔw�i
	GameBackground = LoadGraph("data/Image/galaxy.png");

}


SceneType PlayScene::Update(float deltaTime)
{
	//�J�����̐���
	camera->Update();

	//�v���C���[�̐���
	player->Update(deltaTime);

	MeteoritePopFlag = true;

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//覐Ώo���t���O��true�̎�
			if (MeteoritePopFlag)
			{
				MeteoritePopFlag = false;

				//覐ΐ���
				meteorite[i]->Update(deltaTime, player);

				//�v���C���[��覐΂̓����蔻��
				hitchecker->PlayerAndMeteorite(player, meteorite);
			}
		}
	}


	//�f�o�b�N�p
	x = player->GetPosition().x;
	y = player->GetPosition().y;
	Direction = hitchecker->GetDirection();

	//HitChecker�̃X�R�A���擾
	TargetScore = hitchecker->GetScore();

	//�X�R�A��ڕW�X�R�A�ɑ����������鏈��
	if (TargetScore != Score)
	{
		if (TargetScore > Score)
		{
			Score += 100;
		}
		else
		{
			Score -= 100;
		}
	}
	
	NowTime = GetNowCount();
	CountDown = GameTime - (NowTime - StartTime) / 1000;

	//�������Ԃ�0�ɂȂ�����
	if (CountDown == 0)
	{
		clsDx();
		NowSceneType = SceneType::RESULT;
	}

	return NowSceneType;
}

void PlayScene::Draw()
{
	//�Q�[����ʔw�i�`��
	DrawBillboard3D(VGet(0.0f, 300.0f, 1200.0f), 0.5f, 0.5f, 4000.0f, 0.0f, GameBackground, TRUE);

	//�v���C���[�`��
	player->Draw();

	for (int i = 0; i < Meteorite::METEORITE_ARRAY_NUMBER; i++)
	{
		if (meteorite[i] != nullptr)
		{
			//覐Ε`��
			meteorite[i]->Draw();
		}
	}

	
	SetFontSize(60);			//�����̃t�H���g�T�C�Y�ύX
	ChangeFont("�l�r ����");	//��ނ�MS�����ɕύX

	//�������ԕ\��
	DrawFormatString(500, 100, GetColor(255, 0, 0), "TIME : %d", CountDown);

	//�l���X�R�A�\��
	DrawFormatString(500, 150, GetColor(255, 255, 0), "SCORE : %d", Score);

	//�f�o�b�N�p
	DrawFormatString(500, 400, GetColor(255, 0, 0), "x : %d", x);
	DrawFormatString(500, 450, GetColor(255, 0, 0), "y : %d", y);
	DrawFormatString(500, 500, GetColor(255, 0, 0), "Direction : %f", Direction);
}