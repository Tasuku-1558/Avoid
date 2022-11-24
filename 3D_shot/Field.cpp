#include "Field.h"
#include "ModelManager.h"


const VECTOR Field::SIZE = VGet(4.0f, 1.0f, 4.0f);
const VECTOR Field::POSITION = VGet(0.0f, -50.0f, 5.0f);
const VECTOR Field::ROTATE = VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f);

Field::Field()
	: rotateAngle()
	, line(0)
{
	//処理なし
}

Field::~Field()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL || line != NULL)
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

	line = LoadGraph("data/image/line.png");
}

void Field::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	DeleteGraph(line);
	line = NULL;
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

	DrawBillboard3D(VGet(0.0f, 120.0f, 230.0f), 0.5f, 0.5f, 1100.0f, 0.0f, line, TRUE);
}
