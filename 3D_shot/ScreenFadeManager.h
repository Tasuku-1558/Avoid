#pragma once

#include "DxLib.h"

//��ʌ��ʃN���X
//�V���O���g��
class ScreenFadeManager final
{
public:
	static ScreenFadeManager& GetInstance();		//�A�h���X��Ԃ�

	void Update();
	void Draw();

	void FadeIn();
	void FadeOut();
	void Reset();

private:

	 ScreenFadeManager();								//�R���X�g���N�^
	 ScreenFadeManager(const ScreenFadeManager&);		//�R�s�[�R���X�g���N�^
	~ScreenFadeManager();								//�f�X�g���N�^

	//�ÓI�萔
	static const int FRAME_NUMBER;
};