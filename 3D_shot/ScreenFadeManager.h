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
	void Reset();		//�������Ȃ珈�����I��
	bool IsFinish();	//�������I����Ă��邩�ǂ���

private:

	 ScreenFadeManager();								//�R���X�g���N�^
	 ScreenFadeManager(const ScreenFadeManager&);		//�R�s�[�R���X�g���N�^
	~ScreenFadeManager();								//�f�X�g���N�^

	void UpdateFadeIn();
	void DrawFadeIn();
	void UpdateFadeOut();
	void DrawFadeOut();

	void(ScreenFadeManager::* pUpdate)();	//Update�֐��|�C���^
	void(ScreenFadeManager::* pDraw)();		//Draw�֐��|�C���^

	int remainingDrawFrame;  // �c��̕`�悷��frame��
	int alphaParameter; // ALPHA�l(0�`255)

	//�ÓI�萔
	static const int FRAME_AMOUNT;		//�t���[����
};