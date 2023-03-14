#include "Field.h"
#include "ModelManager.h"


const string Field::IMAGE_FOLDER_PATH = "data/image/";						//imageフォルダまでのパス
const string Field::LINE_PATH		  = "line.png";							//ライン画像のパス
const VECTOR Field::SIZE	 = { 6.0f, 1.0f, 3.0f };						//モデルの倍率
const VECTOR Field::POSITION = { 0.0f, -50.0f, 1200.0f };					//モデルの位置
const VECTOR Field::ROTATE	 = { 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f };	//モデルの回転


/// <summary>
/// コンストラクタ
/// </summary>
Field::Field()
	: rotate()
	, lineHandle(0)
{
	//処理なし
}

Field::~Field()
{
	Finalize();
}

void Field::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::FIELD));
	MV1SetScale(modelHandle, SIZE);

	position = POSITION;
	rotate = ROTATE;

	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotate);

	string failePath = IMAGE_FOLDER_PATH + LINE_PATH;
	lineHandle = LoadGraph(failePath.c_str());
}

void Field::Finalize()
{
	MV1DeleteModel(modelHandle);

	DeleteGraph(lineHandle);
}

void Field::Activate()
{
	//処理なし
}

void Field::Draw()
{
	MV1DrawModel(modelHandle);

	DrawBillboard3D(VGet(0.0f, 120.0f, 230.0f), 0.5f, 0.5f, 1100.0f, 0.0f, lineHandle, TRUE);
}
