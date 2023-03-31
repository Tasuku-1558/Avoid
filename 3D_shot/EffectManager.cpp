#include "EffectManager.h"
#include "Effect.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectManager::EffectManager()
	: EFFECT_FOLDER_PATH("Data/Effect/")
	, EXPLOSION_EFFECT_PATH("Explosion/Explosion.efkefc")
	, FIRE_EFFECT_PATH("Fire/Fire.efkefc")
	, EXPLOSION_SIZE(30.0f)
	, FIRE_SIZE(30.0f)
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectManager::~EffectManager()
{
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		delete effect[i];
	}
}

/// <summary>
/// ����������
/// </summary>
void EffectManager::Initialize()
{
	//�e�G�t�F�N�g�̓ǂݍ���
	effect[0] = new Effect(InputPath(EFFECT_FOLDER_PATH, EXPLOSION_EFFECT_PATH), EXPLOSION_SIZE);
	effect[1] = new Effect(InputPath(EFFECT_FOLDER_PATH, FIRE_EFFECT_PATH), FIRE_SIZE);
}

/// <summary>
/// �`�揈��
/// </summary>
void EffectManager::Draw()
{
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		effect[i]->Draw();
	}
}

/// <summary>
/// �G�t�F�N�g�̐���
/// </summary>
/// <param name="number">�G�t�F�N�g�̎��</param>
/// <param name="position">�G�t�F�N�g�̈ʒu</param>
void EffectManager::CreateEffect(int number, VECTOR position)
{
	effect[number]->Update(position);
}

/// <summary>
/// �G�t�F�N�g�p�X�̓���
/// </summary>
/// <param name="folderPath">�G�t�F�N�g�t�H���_�[�̃p�X</param>
/// <param name="effectPath">�G�t�F�N�g�̃p�X</param>
/// <returns>�G�t�F�N�g�̃p�X</returns>
string EffectManager::InputPath(string folderPath, string effectPath)
{
	return string(folderPath + effectPath);
}