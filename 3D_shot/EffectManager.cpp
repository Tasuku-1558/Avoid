#include "EffectManager.h"
#include "Effect.h"
#include "InputManager.h"

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
	DeleteEffect();
}

/// <summary>
/// ����������
/// </summary>
void EffectManager::Initialize()
{
	Effects effects[] =
	{
		{EXPLOSION_EFFECT_PATH, EXPLOSION_SIZE},
		{FIRE_EFFECT_PATH,		FIRE_SIZE},
	};

	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		//�e�G�t�F�N�g�̓ǂݍ���
		effect[i] = new Effect(Input::InputPath(EFFECT_FOLDER_PATH, effects[i].effectPath), effects[i].effectSize);
	}
}

/// <summary>
/// �G�t�F�N�g�̍폜
/// </summary>
void EffectManager::DeleteEffect()
{
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		if (effect[i] != NULL)
		{
			delete effect[i];
			effect[i] = NULL;
		}
	}
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
/// <param name="position">�G�t�F�N�g�̈ʒu</param>
/// <param name="effectType">�G�t�F�N�g�̎��</param>
void EffectManager::CreateEffect(VECTOR position, EffectType effectType)
{
	effect[effectType]->Update(position);
}