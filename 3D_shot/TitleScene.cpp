#include "TitleScene.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "UiManager.h"
#include "PlayScene.h"

TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, titleImage(0)
	, titleBackgroundX(0)
	, titleBackgroundY(0)
	, titleName(0)
	, titleUi(0)
	, playScene(nullptr)
{
	//処理なし
}

TitleScene::~TitleScene()
{
	//処理なし
}

void TitleScene::Receive(PlayScene* inPlayScene)
{
	playScene = inPlayScene;
}

void TitleScene::Initialize()
{
	titleImage = LoadGraph("data/image/ui0.png");
	titleName = LoadGraph("data/image/ui1.png");
	titleUi = LoadGraph("data/image/ui2.png");
}

void TitleScene::Finalize()
{
}

void TitleScene::Activate()
{
}

void TitleScene::Update(float deltaTime)
{
	//次のシーンへ
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		parent->SetNextScene(SceneManager::PLAY);
		return;
	}
}

//文字を明滅
void TitleScene::Blink()
{
	// 明滅ルーチン
	static int alpha = 0;
	static int inc = 3;

	if (alpha > 255 && inc > 0)
		inc *= -1;

	if (alpha < 0 && inc < 0)
		inc *= -1;

	alpha += inc;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	
	DrawGraph(500, 700, titleUi, TRUE);
	//playScene->uiManager->DrawTitle();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

void TitleScene::Draw()
{
	DrawGraph(titleBackgroundX, titleBackgroundY, titleImage, TRUE);

	DrawGraph(350, 450, titleName, TRUE);
	
	Blink();
}