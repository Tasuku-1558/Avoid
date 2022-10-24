#include "SceneManager.h"
#include "Common.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"

SceneManager::SceneManager()
	: eachScene()
	, nowPointer(nullptr)
	, nowScene()
	, nextScene()
{
	//�����Ȃ�
}

SceneManager::~SceneManager()
{
	//�����Ȃ�
}

void SceneManager::Initialize()
{
	eachScene[TITLE]  = new TitleScene(this);
	eachScene[PLAY]   = new PlayScene(this);
	eachScene[RESULT] = new ResultScene(this);

	//�S�ẴV�[���̏�����
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScene[i]->Initialize();
	}

	//�ŏ��̃V�[���̏������Ɗ�����
	nowScene = nextScene = TITLE;
	
	nowPointer = eachScene[nowScene];
	nowPointer->Activate();
}

void SceneManager::Finalize()
{
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScene[i]->Finalize();
		SafeDelete(eachScene[i]);
	}
}

void SceneManager::Update(float deltaTime)
{
	//���̃V�[�����Z�b�g����Ă����玟��
	if (nowScene != nextScene)
	{
		ChangeScene();						//���̃V�[��
	}

	if (nowPointer != nullptr)
	{
		nowPointer->Update(deltaTime);		//���̃V�[���̍X�V����
	}
}

void SceneManager::Draw()
{
	if (nowPointer != nullptr)
	{
		nowPointer->Draw();					//���̃V�[���̕`�揈��
	}
}

void SceneManager::SetNextScene(Scene next)
{
	nextScene = next;
}

void SceneManager::ChangeScene()
{
	if (nextScene == END)
	{
		return;
	}

	nowPointer = eachScene[nextScene];	//���̃V�[����
	nowScene = nextScene;
	nowPointer->Activate();				//���̃V�[����������
}

//���̃V�[�����擾
SceneManager::Scene SceneManager::GetNowScene()
{
	return nowScene;
}

//���̃V�[�����擾
SceneManager::Scene SceneManager::GetNextScene()
{
	return nextScene;
}