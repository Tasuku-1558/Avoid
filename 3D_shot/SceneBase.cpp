#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneType">�V�[���̎��</param>
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
/// <param name="nowScene">���݂̃V�[��</param>
/// <returns>�V�[����Ԃ�</returns>
SceneBase* SceneBase::CreateScene(SceneType nowScene)
{
	SceneBase* retScene = nullptr;

	switch (nowScene)
	{
	case SceneType::TITLE:
		retScene = new TitleScene();
		break;

	case SceneType::GAME:
		retScene = new GameScene();
		break;
	}

	return retScene;
}