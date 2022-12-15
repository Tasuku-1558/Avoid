#include "ScreenFadeManager.h"
#include "Common.h"


const int ScreenFadeManager::FRAME_AMOUNT = 10;	//�t���[����

//�R���X�g���N�^
ScreenFadeManager::ScreenFadeManager()
	: remainingDrawFrame(0)
	, alphaParameter(0)
	, pUpdate(nullptr)
	, pDraw(nullptr)
{
	//�����Ȃ�
}

//�f�X�g���N�^
ScreenFadeManager::~ScreenFadeManager()
{
	// �g�p���Ȃ�
}

ScreenFadeManager& ScreenFadeManager::GetInstance()
{
	static ScreenFadeManager screenFadeManager;
	return screenFadeManager;
}

//�X�V����
void ScreenFadeManager::Update()
{
	//�������Ȃ���Ώ������Ȃ�
	if (pUpdate == nullptr)
	{
		return;
	}

	(this->*pUpdate)();

	--remainingDrawFrame;	//�t���[��������
}

//�`�揈��
void ScreenFadeManager::Draw()
{
	//�������Ȃ���Ώ������Ȃ�
	if (pDraw == nullptr)
	{
		return;
	}

	(this->*pDraw)();
}

void ScreenFadeManager::FadeIn()
{
	//�������ł���Ώ������Ȃ�
	if (pUpdate != nullptr)
	{
		return;
	}

	remainingDrawFrame = FRAME_AMOUNT;

	//�֐��|�C���^�Ƀt�F�[�h�C�����Z�b�g
	pUpdate = &ScreenFadeManager::UpdateFadeIn;
	pDraw   = &ScreenFadeManager::DrawFadeIn;
}

void ScreenFadeManager::FadeOut()
{
	//�������ł���Ώ������Ȃ�
	if (pUpdate != nullptr)
	{
		return;
	}

	remainingDrawFrame = FRAME_AMOUNT;

	//�֐��|�C���^�Ƀt�F�[�h�C�����Z�b�g
	pUpdate = &ScreenFadeManager::UpdateFadeOut;
	pDraw   = &ScreenFadeManager::DrawFadeOut;
}

void ScreenFadeManager::Reset()
{
	// �������łȂ��Ȃ珈�����Ȃ�
	if (pUpdate == nullptr)
	{
		return;
	}

	remainingDrawFrame = 0;
	pUpdate = nullptr;
	pDraw = nullptr;
}

void ScreenFadeManager::UpdateFadeIn()
{
	// �c��t���[�������Ȃ���Ώ�������
	if (remainingDrawFrame <= 0)
	{
		pUpdate = nullptr;
		pDraw = nullptr;
		return;
	}

	float percentage = static_cast<float>(remainingDrawFrame) / static_cast<float>(FRAME_AMOUNT);	// �c��t���[����
	alphaParameter = static_cast<int>(percentage * 255.0f);											// 0����255�̒l�ɕϊ�
}

void ScreenFadeManager::UpdateFadeOut()
{
	// �c��t���[�������Ȃ���Ώ�������
	if (remainingDrawFrame <= 0)
	{
		pUpdate = nullptr;
		return;
	}

	float percentage = static_cast<float>(remainingDrawFrame) / static_cast<float>(FRAME_AMOUNT);	// �c��t���[����
	alphaParameter = static_cast<int>(percentage * 255.0f);											// 0����255�̒l�ɕϊ�
	alphaParameter = 255 - alphaParameter;															// �A���t�@�l��ϊ�
}

void ScreenFadeManager::DrawFadeIn()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaParameter); // �u�����h���[�h�ύX
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xff000000, TRUE);   // ���l�p�`�̕`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // �u�����h���[�h�����ɖ߂�
}

void ScreenFadeManager::DrawFadeOut()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaParameter); // �u�����h���[�h�ύX
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xff000000, TRUE);   // ���l�p�`�̕`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // �u�����h���[�h�����ɖ߂�
}

bool ScreenFadeManager::IsFinish()
{
	if (pUpdate == nullptr)
	{
		return true;
	}

	return false;
}
