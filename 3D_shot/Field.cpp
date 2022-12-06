#include "Field.h"
#include "ModelManager.h"


const VECTOR Field::SIZE	 = { 6.0f, 1.0f, 3.0f };						//モデルの倍率
const VECTOR Field::POSITION = { 0.0f, -50.0f, 1200.0f };					//モデルの位置
const VECTOR Field::ROTATE	 = { 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f };	//モデルの回転

Field::Field()
	: rotateAngle()
	, lineHandle(0)
{
	//処理なし
}

Field::~Field()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL || lineHandle != NULL)
	{
		Finalize();
	}
}

void Field::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::FIELD));
	MV1SetScale(modelHandle, SIZE);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [FIELD]\n");
	}

	lineHandle = LoadGraph("data/image/line.png");
}

void Field::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	DeleteGraph(lineHandle);
	lineHandle = NULL;
}

void Field::Activate()
{
	position = POSITION;
	rotateAngle = ROTATE;

	
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotateAngle);
}

void Field::Draw()
{
	MV1DrawModel(modelHandle);

	DrawBillboard3D(VGet(0.0f, 120.0f, 230.0f), 0.5f, 0.5f, 1100.0f, 0.0f, lineHandle, TRUE);
}
