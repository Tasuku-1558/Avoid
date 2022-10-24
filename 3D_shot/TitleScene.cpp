#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"

const int TitleScene::TITLE_NAME_X = 600;
const int TitleScene::TITLE_NAME_Y = 500;


TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, titleImage(0)
	, titleBackgroundX(0)
	, titleBackgroundY(0)
	, titleName{ "Just in Avoid" }
{
	//処理なし
}

TitleScene::~TitleScene()
{
	//処理なし
}

void TitleScene::Initialize()
{
	titleImage = LoadGraph("data/Image/TitleBackground.png");
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
	static int Alpha = 0;
	static int Inc = 5;

	if (Alpha > 255 && Inc > 0)
		Inc *= -1;

	if (Alpha < 0 && Inc < 0)
		Inc *= -1;

	Alpha += Inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	DrawFormatString(200, 700, GetColor(255, 0, 0), "Push Space Key To GameStart!");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);
}

void TitleScene::Draw()
{
	DrawGraph(titleBackgroundX, titleBackgroundY, titleImage, TRUE);

	ChangeFont("ＭＳ 明朝");	//種類をMS明朝に変更
	SetFontSize(110);			//文字のフォントサイズ変更

	DrawString(TITLE_NAME_X, TITLE_NAME_Y, titleName, GetColor(170, 200, 200));

	Blink();
}