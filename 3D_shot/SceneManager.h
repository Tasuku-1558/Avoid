#pragma once

class SceneBase;

/// <summary>
/// シーンマネージャークラス
/// </summary>
class SceneManager final
{
public:

	/// <summary>
	/// シーンの状態
	/// </summary>
	enum Scene
	{
		TITLE,			//タイトル画面
		PLAY,			//ゲーム画面
		RESULT,			//リザルト画面
		END				//終了とシーン数
	};

	SceneManager();
   ~SceneManager();

   void Initialize();
   void Finalize();
   void Update(float deltaTime);
   void Draw();

   void  SetNextScene(Scene next);		//次のシーンをセット
   Scene GetNowScene();					//今のシーンを取得
   Scene GetNextScene();				//次のシーンを取得

private:

	SceneManager(const SceneManager&);	//コピーコンストラクタ

	SceneBase* eachScene[Scene::END];	//各シーンのインスタンス
	SceneBase* nowPointer;				//今のシーンポインタ
	Scene	   nowScene;				//今のシーン
	Scene	   nextScene;				//次のシーン

	void ChangeScene();					//シーンの変更
};