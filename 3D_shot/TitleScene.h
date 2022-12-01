#pragma once

#include "SceneBase.h"

//タイトルシーンクラス
class TitleScene final : public SceneBase
{
public:
	 TitleScene(SceneManager* const sceneManager);
	~TitleScene();

	void Initialize();					//初期化
	void Finalize();
	void Activate();
	void Update(float deltaTime);		//更新
	void Draw();						//描画
	
private:

	TitleScene(const TitleScene&);		//コピーコンストラクタ

	void Blink();						//文字を明滅

	int backGroundHandle;

	int titleName;
	int titleUi;
};