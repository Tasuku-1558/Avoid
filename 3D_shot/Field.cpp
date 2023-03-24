#include "Field.h"
#include "ModelManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Field::Field()
	: lineHandle(0)
	, IMAGE_FOLDER_PATH("Data/image/")
	, LINE_PATH("line.png")
	, SIZE({ 6.0f, 1.0f, 3.0f })
	, POSITION({ 0.0f, -50.0f, 1200.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Field::~Field()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void Field::Initialize()
{
	//�t�B�[���h���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::FIELD));

	//�t�B�[���h���f���̈ʒu,�T�C�Y,��]�l��ݒ�
	MV1SetPosition(modelHandle, POSITION);
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	//���C���摜�̓ǂݍ���
	string failePath = IMAGE_FOLDER_PATH + LINE_PATH;
	lineHandle = LoadGraph(failePath.c_str());
}

/// <summary>
/// �I������
/// </summary>
void Field::Finalize()
{
	MV1DeleteModel(modelHandle);

	DeleteGraph(lineHandle);
}

/// <summary>
/// �`�揈��
/// </summary>
void Field::Draw()
{
	MV1DrawModel(modelHandle);

	DrawBillboard3D(VGet(0.0f, 120.0f, 230.0f), 0.5f, 0.5f, 1100.0f, 0.0f, lineHandle, TRUE);
}