//-----------------------------------------------------------------------------
// @brief  ���C������
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Common.h"
#include "SceneManager.h"
#include "ModelManager.h"

#pragma warning(disable:4996)

using std::string;

//-----------------------------------------------------------------------------
// @brief  ���C���֐�
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);			// ���O�t�@�C�����o�͂��Ȃ�
	ChangeWindowMode(IS_WINDOW_MODE);				// �E�B���h�E���[�h�ɂ��邩
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);	// ��ʃ��[�h�̃Z�b�g
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// DX���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// Effekseer������������
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}
	
	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// ���Ԍv��
	int nowTime = GetNowCount();
	int prevTime = nowTime;

	ModelManager::GetInstance();	//���f���Ǘ��N���X�̐���

	SceneManager* sceneManager = new SceneManager();

	sceneManager->Initialize();

	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �t���[�����Ԃ��Z�o
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime) / 1000.0f;

		// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
		Effekseer_Sync3DSetting();

		sceneManager->Update(deltaTime);

		// ��ʂ�����������
		ClearDrawScreen();

		sceneManager->Draw();

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

		//���̃V�[����END�Ȃ�
		if (sceneManager->GetNextScene() == SceneManager::END)
		{
			break;
		}
		
		prevTime = nowTime;
	}

	SafeDelete(sceneManager);	// �V�[���}�l�[�W���[�̉��

	Effkseer_End();			// Effekseer�̏I������
	
	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}