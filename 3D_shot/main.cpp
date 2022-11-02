//-----------------------------------------------------------------------------
// ���C������
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Common.h"
#include "SceneManager.h"
#include "ModelManager.h"

#pragma warning(disable:4996)

using std::string;

void FeverGauge(int hp, int hpMax)
{
	int color = GetColor(255, 255, 0);
	
	DrawBox(1200,100, 900, 300, color, FALSE);			//�g��`��
	DrawBox(800, 500, 100 + 500 * hp / hpMax, 130, color, TRUE);	//HP�Q�[�W��`��
}
//-----------------------------------------------------------------------------
// ���C���֐�
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

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// ���Ԍv��
	int nowTime = GetNowCount();
	int prevTime = nowTime;
	int hp = 0, hpMax = 180;
	ModelManager::GetInstance();	//���f���Ǘ��N���X�̐���

	SceneManager* sceneManager = new SceneManager();

	sceneManager->Initialize();

	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �t���[�����Ԃ��Z�o
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime) / 1000.0f;

		// DX���C�u�����̃J������Effekseer�̃J�����𓯊�
		Effekseer_Sync3DSetting();

		if (CheckHitKey(KEY_INPUT_V))
		{
			hp += 1;

			if (hp >= hpMax)
			{
				hp = 0;
			}
		}
		
		sceneManager->Update(deltaTime);

		// ��ʂ�����������
		ClearDrawScreen();

		sceneManager->Draw();
		//FeverGauge(hp, hpMax);
		
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

	Effkseer_End();				// Effekseer�̏I������
	
	DxLib_End();				// DX���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I�� 
}