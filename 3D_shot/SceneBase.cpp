#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneType"></param>
SceneBase::SceneBase(SceneType sceneType)
	: nowSceneType(sceneType)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{
	//処理なし
}

/// <summary>
/// 新しいシーンを生成する
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