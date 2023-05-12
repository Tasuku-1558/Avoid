#pragma once

#include "EffectBase.h"

/// <summary>
/// �G�t�F�N�g�Ǘ��N���X
/// </summary>
class EffectManager final
{
public:
	EffectManager();
	virtual ~EffectManager();

	//�G�t�F�N�g�̎��
	enum EffectType
	{
		EXPLOSION,			//�����G�t�F�N�g
		FIRE,				//���G�t�F�N�g
		EFFECT_AMOUNT,		//�G�t�F�N�g�̎��
	};

	void Draw();			//�`�揈��

	void CreateEffect(VECTOR position, EffectType effectType);	//�G�t�F�N�g�̐���

private:
	EffectManager(const EffectManager&);	//�R�s�[�R���X�g���N�^

	void Initialize();						//����������
	void DeleteEffect();					//�G�t�F�N�g�̍폜

	EffectBase* effect[EFFECT_AMOUNT];		//�G�t�F�N�g�i�[�p

	struct Effects
	{
		string effectPath;	//�G�t�F�N�g�̃p�X
		float  effectSize;	//�G�t�F�N�g�̃T�C�Y
	};

	//�G�t�F�N�g
	const string EFFECT_FOLDER_PATH;		//Effect�t�H���_�܂ł̃p�X
	const string EXPLOSION_EFFECT_PATH;		//�����G�t�F�N�g�̃p�X
	const string FIRE_EFFECT_PATH;			//���G�t�F�N�g�̃p�X

	//�G�t�F�N�g�̃T�C�Y
	const float  EXPLOSION_SIZE;			//�����G�t�F�N�g�̃T�C�Y
	const float  FIRE_SIZE;					//���G�t�F�N�g�̃T�C�Y

};