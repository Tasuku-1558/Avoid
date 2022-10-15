//-----------------------------------------------------------------------------
// @brief  ���C������
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "ModelManager.h"
#include "Common.h"
#include "Utility.h"

#pragma warning(disable:4996)

using std::string;


//�V�����V�[���𐶐�����
SceneBase* CreateScene(SceneType Now)
{
	SceneBase* RetScene = nullptr;

	switch (Now)
	{
	case SceneType::TITLE:
		RetScene = new TitleScene;
		break;

	case SceneType::PLAY:
		RetScene = new PlayScene;
		break;

	case SceneType::RESULT:
		RetScene = new ResultScene;
		break;

	default:
		break;
	}
	return RetScene;
}

//-----------------------------------------------------------------------------
// @brief  ���C���֐�
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);			// ���O�t�@�C�����o�͂��Ȃ�
	ChangeWindowMode(IS_WINDOW_MODE);				// �E�B���h�E���[�h�ɂ��邩
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);	//��ʃ��[�h�̃Z�b�g

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//�ЂƂO�̃V�[��
	SceneType PrevSceneType = SceneType::PLAY/*TITLE*/;

	//���̃V�[��
	SceneType NowSceneType = SceneType::PLAY/*TITLE*/;
	
	// ���Ԍv��
	int nowTime = GetNowCount();
	int prevTime = nowTime;
	
	//�V�[���𐶐�
	SceneBase* scenebase = new PlayScene/*TitleScene*/;

	ModelManager::GetInstance();	//���f���Ǘ��N���X�̐���
	
	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �t���[�����Ԃ��Z�o
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime) / 1000.0f;
		
		scenebase->Initialize();

		NowSceneType = scenebase->Update(deltaTime);

		// ��ʂ�����������
		ClearDrawScreen();

		scenebase->Draw();
		
		//�ʒu�֌W���킩��悤��
		//��ŏ���
		{
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
		}

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		//SceneType���؂�ւ������V�[���̐؂�ւ�
		if (NowSceneType != PrevSceneType)
		{
			SAFE_DELETE(scenebase);						//�V�[���̉��
			scenebase = CreateScene(NowSceneType);		//�V�[���̐���
		}


		prevTime = nowTime;

		//���O�̃V�[�����L�^
		PrevSceneType = NowSceneType;
	}

	SAFE_DELETE(scenebase);	//�V�[���̉��
	
	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}