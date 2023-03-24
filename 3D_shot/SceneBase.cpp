#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneType"></param>
SceneBase::SceneBase(SceneType sceneType)
	: nowSceneType(sceneType)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneBase::~SceneBase()
{
	//�����Ȃ�
}

/// <summary>
/// �V�����V�[���𐶐�����
/// </summary>
/// <param name="nowScene"></param>
/// <returns></returns>
SceneBase* SceneBase::CreateScene(SceneType nowScene)
{
	SceneBase* retScene = nullptr;

	switch (nowScene)
	{
	case SceneType::TITLE:
		retScene = new TitleScene();
		break;

	case SceneType::PLAY:
		retScene = new PlayScene();
		break;

	case SceneType::RESULT:
		retScene = new ResultScene();
		break;
	}

	return retScene;
}