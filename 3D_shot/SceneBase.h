#pragma once


//シーンの種類
enum class SceneType
{
	TITLE,
	PLAY,
	RESULT
};


class SceneBase
{
public:
	SceneBase(SceneType sceneType):NowSceneType(sceneType){ /*処理なし*/} //コンストラクタ
	virtual ~SceneBase(){/*処理なし*/} //デストラクタ

	virtual void Initialize() = 0;
	virtual SceneType Update(float deltaTime) = 0;
	virtual void Draw() = 0;

protected:
	SceneType NowSceneType;
};