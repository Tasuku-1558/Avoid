#include "UiManager.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, numberImage()
	, alpha(255)
	, inc(-1)
	, displayTime(0)
	, alphaEnd(false)
	, MAX_ALPHA(255)
	, MAX_DISPLAY_TIME(400)
	, INITIAL_DISPLAY_TIME(0)
	, INC_SPEED(-1)
	, GAME_UI_NUMBER(3)
	, COUNTDOWN_IMAGE_NUMBER(3)
	, WAVE_CATEGORY(4)
	, WAVE2_TIME(80)
	, WAVE3_TIME(60)
	, WAVE4_TIME(40)
	, WAVE5_TIME(20)
	, TOTAL_COUNT(3)
	, LANDSCAPE_COUNT(3)
	, PORTRAIT_COUNT(1)
	, SIZE_X(466)
	, SIZE_Y(467)
	, NUMBER_IMAGE_POS_X(720)
	, NUMBER_IMAGE_POS_Y(300)
	, WAVE_IMAGE_POS_X(0)
	, WAVE_IMAGE_POS_Y(90)
	, TIME_UI_POS_X(500)
	, SCORE_UI_POS_X(1000)
	, WAVE_UI_POS_X(100)
	, GAME_UI_POS_Y(100)
	, FRAME_IMAGE_POS_X(0)
	, FRAME_IMAGE_POS_Y(-150)
	, TIME_UI_COLOR(GetColor(255, 0, 0))
	, SCORE_UI_COLOR(GetColor(255, 255, 0))
	, WAVE_UI_COLOR(GetColor(0, 255, 0))
	, IMAGE_FOLDER_PATH("Data/Image/")
	, UI_GRAPHIC_PATH("ui")
	, COUNTDOWN_GRAPHIC_PATH("CountDown")
	, IMAGE_FILENAME_EXTENSION(".png")
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UiManager::~UiManager()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void UiManager::Initialize()
{
	//Ui�摜�ǂݍ���
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		string uiPath = IMAGE_FOLDER_PATH + UI_GRAPHIC_PATH + to_string(i) + IMAGE_FILENAME_EXTENSION;
		uiHandle[i] = LoadGraph(uiPath.c_str());

		if (uiHandle[i] < 0)
		{
			printfDx("Ui�摜�ǂݍ��݂Ɏ��s[%d]\n", i);
		}
	}

	//�����摜�ǂݍ���
	string numberPath = IMAGE_FOLDER_PATH + COUNTDOWN_GRAPHIC_PATH + IMAGE_FILENAME_EXTENSION;
	LoadDivGraph(numberPath.c_str(), TOTAL_COUNT, LANDSCAPE_COUNT, PORTRAIT_COUNT, SIZE_X, SIZE_Y, numberImage);

	if (numberImage[0] < 0)
	{
		printfDx("�����摜�ǂݍ��݂Ɏ��s\n");
	}
}

/// <summary>
/// �I������
/// </summary>
void UiManager::Finalize()
{
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		DeleteGraph(uiHandle[i]);
		uiHandle[i] = NULL;
	}

	for (int i = 0; i < COUNTDOWN_IMAGE_NUMBER; ++i)
	{
		DeleteGraph(numberImage[i]);
		numberImage[i] = NULL;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="gameState">�Q�[���̏��</param>
/// <param name="frame">�t���[����</param>
/// <param name="font">�Q�[���t�H���g</param>
/// <param name="countDown">�Q�[��������</param>
/// <param name="score">�l���X�R�A</param>
/// <param name="wave">�E�F�[�u</param>
void UiManager::Draw(GameScene::GameState gameState, float frame, int font, int countDown, int score, int wave)
{
	switch (gameState)
	{
	case GameScene::GameState::START:
		StartCountDraw(frame);
		break;

	case GameScene::GameState::GAME:
		FrameDraw();
		GameUiDraw(font, countDown, score, wave);
		WaveDraw(countDown);
		break;
	}
}

/// <summary>
/// �J�E���g�_�E���`��
/// </summary>
/// <param name="frame">�t���[����</param>
void UiManager::StartCountDraw(float frame)
{
	int number = (int)frame;

	DrawGraph(NUMBER_IMAGE_POS_X, NUMBER_IMAGE_POS_Y, numberImage[number], TRUE);
}

/// <summary>
/// �E�F�[�u�`��
/// </summary>
/// <param name="countDown">�Q�[��������</param>
void UiManager::WaveDraw(int countDown)
{
	displayTime++;

	Wave wave[] =
	{
		{WAVE2_TIME, WAVE2},
		{WAVE3_TIME, WAVE3},
		{WAVE4_TIME, WAVE4},
		{WAVE5_TIME, FINAL_WAVE},
	};

	for (int i = 0; i < WAVE_CATEGORY; i++)
	{
		if (countDown == wave[i].time && displayTime > MAX_DISPLAY_TIME)
		{
			WaveAlpha(wave[i].graphic);
		}
	}
}

/// <summary>
/// �E�F�[�u�摜�̓��ߏ���
/// </summary>
/// <param name="graphic">Ui�摜�̎��</param>
void UiManager::WaveAlpha(Graphic graphic)
{
	if (alpha > MAX_ALPHA && inc > 0)
	{
		inc *= INC_SPEED;
	}

	//���߂��I�������
	if (alpha == inc)
	{
		alphaEnd = true;
	}

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawGraph(WAVE_IMAGE_POS_X, WAVE_IMAGE_POS_Y, uiHandle[graphic], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// ���߂̏�����
/// </summary>
void UiManager::AlphaReset()
{
	alphaEnd = false;
	alpha = MAX_ALPHA;
	displayTime = INITIAL_DISPLAY_TIME;
}

/// <summary>
/// �Q�[��Ui�����`��
/// </summary>
/// <param name="font">�Q�[���t�H���g</param>
/// <param name="countDown">�Q�[��������</param>
/// <param name="score">�l���X�R�A</param>
/// <param name="wave">�E�F�[�u</param>
void UiManager::GameUiDraw(int font, int countDown, int score, int wave)
{
	GameUi gameUi[] =
	{
		{TIME_UI_POS_X,  TIME_UI_COLOR,  "TIME : %d",  countDown},
		{SCORE_UI_POS_X, SCORE_UI_COLOR, "SCORE : %d", score},
		{WAVE_UI_POS_X,  WAVE_UI_COLOR,  "WAVE : %d",  wave},
	};

	for (int i = 0; i < GAME_UI_NUMBER; i++)
	{
		//�Q�[��Ui�����̕\��
		DrawFormatStringToHandle(gameUi[i].posX, GAME_UI_POS_Y, gameUi[i].color, font, gameUi[i].name, gameUi[i].uiType);
	}
}

/// <summary>
/// �g�`��
/// </summary>
void UiManager::FrameDraw()
{
	DrawGraph(FRAME_IMAGE_POS_X, FRAME_IMAGE_POS_Y, uiHandle[FRAME], TRUE);
}