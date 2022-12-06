#include "ScreenFadeManager.h"


const int ScreenFadeManager::FRAME_AMOUNT = 120;	//�t���[����

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
}

void ScreenFadeManager::UpdateFadeIn()
{
}

void ScreenFadeManager::DrawFadeIn()
{
}

void ScreenFadeManager::UpdateFadeOut()
{
}

void ScreenFadeManager::DrawFadeOut()
{
}



bool ScreenFadeManager::IsFinish()
{
	return false;
}
