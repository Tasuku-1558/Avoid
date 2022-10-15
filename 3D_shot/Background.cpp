#include "Background.h"
#include "ModelManager.h"

const float  Background::SIZE			  = 9.0f;					//���f���{��
const VECTOR Background::INITIAL_POSITION = { 0.0f,40.0f,0.0f };	//�����ʒu

Background::Background()
	: Position()
	, ModelHandle(0)
{
	//�����Ȃ�
}

Background::~Background()
{
	//�����Ȃ�
}

void Background::Initialize()
{
	ModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BACKGROUND));
	MV1SetScale(ModelHandle, VGet(SIZE, SIZE, SIZE));

	//�ǂݍ��ݎ��s�ŃG���[
	if (ModelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [BACKGROUND]\n");
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
