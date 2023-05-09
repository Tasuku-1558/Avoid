#include "FadeManager.h"
#include <math.h>
#include "PreCompiledHeader.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
FadeManager::FadeManager()
	: fade(0)
	, fadeInc(2)
	, fadeEnd(false)
	, INITIAL_FADE(0)
	, INITIAL_FADE_INC(2)
	, TOP_LEFT_VERTEX_POS_X(0)
	, TOP_LEFT_VERTEX_POS_Y(0)
	, BLACK(GetColor(0, 0, 0))
	, MAX_FADE(255)
	, FADE_SPEED(-1)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FadeManager::~FadeManager()
{
	//�����Ȃ�
}

/// <summary>
/// ��ʌ��ʏ���
/// </summary>
void FadeManager::FadeMove()
{
	//��ʌ��ʂ̑����`�F�b�N
	if (fade > MAX_FADE && fadeInc > 0)
	{
		fadeInc *= FADE_SPEED;
		fadeEnd = true;
	}

	fade += fadeInc;
}

/// <summary>
/// ��ʌ��ʃ��Z�b�g
/// </summary>
void FadeManager::FadeReset()
{
	fade = INITIAL_FADE;
	fadeInc = INITIAL_FADE_INC;
	fadeEnd = false;
}

/// <summary>
/// �`�揈��
/// </summary>
void FadeManager::Draw()
{
	//��ʑS�̃t�F�[�h�p�̋�`���F�̔w�i��`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(TOP_LEFT_VERTEX_POS_X, TOP_LEFT_VERTEX_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, fade);
}