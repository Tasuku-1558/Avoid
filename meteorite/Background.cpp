#include "Background.h"
#include "ModelManager.h"

const float  Background::SIZE			  = 9.0f;					//モデル倍率
const VECTOR Background::INITIAL_POSITION = { 0.0f,40.0f,0.0f };	//初期位置

Background::Background()
	: Position()
	, ModelHandle(0)
{
	//処理なし
}

Background::~Background()
{
	//処理なし
}

void Background::Initialize()
{
	ModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BACKGROUND));
	MV1SetScale(ModelHandle, VGet(SIZE, SIZE, SIZE));

	//読み込み失敗でエラー
	if (ModelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [BACKGROUND]\n");
	}
}

void Background::Update()
{
	Position = INITIAL_POSITION;
	MV1SetPosition(ModelHandle, Position);
}

void Background::Draw()
{
	MV1DrawModel(ModelHandle);
}
