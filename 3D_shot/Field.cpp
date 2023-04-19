#include "Field.h"
#include "ModelManager.h"
#include "InputManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Field::Field()
	: lineImage(0)
	, LINE_CENTER_POSITION(0.5f)
	, LINE_SIZE(1100.0f)
	, LINE_ANGLE(0.0f)
	, SIZE({ 6.0f, 1.0f, 3.0f })
	, POSITION({ 0.0f, -50.0f, 1200.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
	, LINE_POSITION({ 0.0f, 120.0f, 230.0f })
	, IMAGE_FOLDER_PATH("Data/Image/")
	, LINE_PATH("line.png")
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

	//�ʒu�ƃT�C�Y�Ɖ�]�l��ݒ�
	MV1SetPosition(modelHandle, POSITION);
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	//���C���摜�̓ǂݍ���
	lineImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, LINE_PATH).c_str());
}

/// <summary>
/// �I������
/// </summary>
void Field::Finalize()
{
	MV1DeleteModel(modelHandle);

	DeleteGraph(lineImage);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Field::Update(float deltaTime)
{
	//�����Ȃ�
}

/// <summary>
/// �`�揈��
/// </summary>
void Field::Draw()
{
	MV1DrawModel(modelHandle);

	DrawBillboard3D(LINE_POSITION, LINE_CENTER_POSITION, LINE_CENTER_POSITION, LINE_SIZE, LINE_ANGLE, lineImage, TRUE);
}