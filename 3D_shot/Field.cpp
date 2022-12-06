#include "Field.h"
#include "ModelManager.h"


const VECTOR Field::SIZE	 = { 6.0f, 1.0f, 3.0f };						//���f���̔{��
const VECTOR Field::POSITION = { 0.0f, -50.0f, 1200.0f };					//���f���̈ʒu
const VECTOR Field::ROTATE	 = { 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f };	//���f���̉�]

Field::Field()
	: rotateAngle()
	, lineHandle(0)
{
	//�����Ȃ�
}

Field::~Field()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL || lineHandle != NULL)
	{
		Finalize();
	}
}

void Field::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::FIELD));
	MV1SetScale(modelHandle, SIZE);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [FIELD]\n");
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
