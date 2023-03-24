#include "EffectManager.h"
#include "Explosion.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectManager::EffectManager()
	: EFFECT_FOLDER_PATH("Data/effect/")
	, EXPLOSION_EFFECT_PATH("Explosion.efkefc")
	, EXPLOSION_SIZE(30.0f)
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
	effect[0] = new Explosion(InputPath(EFFECT_FOLDER_PATH, EXPLOSION_EFFECT_PATH), EXPLOSION_SIZE);
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
/// �����G�t�F�N�g�̐���
/// </summary>
/// <param name="position">�G�t�F�N�g�̈ʒu</param>
void EffectManager::CreateExplosionEffect(VECTOR position)
{
	effect[EXPLOSION]->Update(position);
}

/// <summary>
/// �G�t�F�N�g�p�X�̓���
/// </summary>
/// <param name="folderPath">�G�t�F�N�g�t�H���_�[�̖��O</param>
/// <param name="effectPath">�G�t�F�N�g�̖��O</param>
/// <returns>�G�t�F�N�g�̃p�X</returns>
string EffectManager::InputPath(string folderPath, string effectPath)
{
	return string(folderPath + effectPath);
}