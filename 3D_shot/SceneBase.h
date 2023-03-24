#pragma once

//シーンの種類
enum class SceneType
{
	TITLE,			//タイトル画面
	PLAY,			//ゲーム画面
	RESULT,			//リザルト画面
	END,			//終了
};

/// <summary>
/// シーンベースクラス
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneType sceneType);
	virtual ~SceneBase();

	virtual void Initialize() = 0;					//初期化処理
	virtual void Activate() = 0;					//活性化処理
	virtual SceneType Update(float deltaTime) = 0;	//更新処理
	virtual void Draw() = 0;						//描画処理

	SceneBase* CreateScene(SceneType nowScene);		//新しいシーンを生成する

protected:
	SceneType nowSceneType;				//今のシーン

private:
	SceneBase(const SceneBase&);		//コピーコンストラクタ
};