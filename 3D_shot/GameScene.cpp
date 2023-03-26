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
#include "Score.h"
#include "TimeSlow.h"


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
	, font(0)
	, targetScore(0)
	, wave(0)
	, shadowMapHandle(0)
	, frame(0.0f)
	, meteoritePopCount(0.0f)
	, slow(false)
	, pUpdate(nullptr)
	, GAME_TIME(20)
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
	for (auto meteoritePtr : meteorite)
	{
		DeleteMeteorite(meteoritePtr);
	}

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);

	//�V���h�E�}�b�v�̍폜
	DeleteShadowMap(shadowMapHandle);
}

/// <summary>
/// ����������
/// </summary>
void GameScene::Initialize()
{
	camera = new Camera();

	/*light = new Light();
	light->GameLight();*/

	backGround = new BackGround();

	field = new Field();

	player = new Player();

	effectManager = new EffectManager();

	evaluation = new Evaluation();

	hitChecker = new HitChecker(effectManager, evaluation);

	uiManager = new UiManager();

	scoreEarn = new ScoreEarn();

	fadeManager = new FadeManager();

	font = CreateFontToHandle("Oranienbaum", 80, 1);

	//�V���h�E�}�b�v�n���h���̍쐬
	shadowMapHandle = MakeShadowMap(SCREEN_WIDTH, SCREEN_HEIGHT);

	//�V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(shadowMapHandle, LIGHT_DIRECTION);

	//�V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	SetShadowMapDrawArea(shadowMapHandle, SHADOWMAP_MINPOSITION, SHADOUMAP_MAXPOSITION);

	pUpdate = &GameScene::UpdateStart;
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
		/*gameState = GameState::RESULT;
		pUpdate = &GameScene::UpdateResult;*/

		nowSceneType = SceneType::RESULT;
	}
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

	if (meteoritePopCount > 1.2f)
	{
		Meteorite* newMeteorite = new Meteorite(player);
		EntryMeteorite(newMeteorite);
		meteoritePopCount = 0.0f;
		wave = 1;
	}
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
	Score::GetInstance().Activate();

	TimeSlow::GetInstance().SetTimeSlow(slow);

	//�Q�[���N�����̎��Ԃ��擾
	startTime = GetNowCount();

	gameState = GameState::GAME;
	pUpdate = &GameScene::UpdateWave1;
}

/// <summary>
/// Wave1
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateWave1(float deltaTime)
{
	backGround->Update();

	player->Update(deltaTime);

	//覐΂̏o���Ԋu
	MeteoritePop(deltaTime);
	
	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Update(deltaTime);

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
			pUpdate = &GameScene::UpdateFinal;
		}

		//覐΂ƏՓ˂����������͐������Ԃ�0�ɂȂ�����覐΂�����
		if (hitChecker->Hit() || countDown == 0)
		{
			DeleteMeteorite(meteoritePtr);
		}
	}

	//�v���C���[��覐΂̏Փ˔���
	hitChecker->PlayerAndMeteorite(player, &meteorite, scoreEarn);

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
void GameScene::UpdateFinal(float deltaTime)
{
	UpdateWave1(deltaTime);
}

void GameScene::GameFinish(float deltaTime)
{
}

/// <summary>
/// ���ʉ��
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateResult(float deltaTime)
{
}

/// <summary>
/// �`�揈��
/// </summary>
void GameScene::Draw()
{
	backGround->Draw();

	field->Draw();

	//�V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(shadowMapHandle);

	player->Draw();

	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Draw();
	}

	//�V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	//�`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(0, shadowMapHandle);

	player->Draw();

	for (auto meteoritePtr : meteorite)
	{
		meteoritePtr->Draw();
	}

	//�`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	SetUseShadowMap(0, -1);

	effectManager->Draw();

	evaluation->Draw();

	uiManager->Draw(gameState, font, countDown, score, wave);

	if (gameState == GameState::RESULT || gameState == GameState::FINISH)
	{
		fadeManager->Draw();
	}
}