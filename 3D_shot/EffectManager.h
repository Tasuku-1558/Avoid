#pragma once

#include "EffectBase.h"
#include <string>


using namespace std;

/// <summary>
/// �G�t�F�N�g�Ǘ��N���X
/// </summary>
class EffectManager final
{
public:
	EffectManager();
	virtual ~EffectManager();

	//�G�t�F�N�g�̎��
	enum Effect
	{
		EXPLOSION,			//�����G�t�F�N�g
		EFFECT_AMOUNT,		//�G�t�F�N�g�̎��
	};

	void Initialize();		//����������
	void Draw();			//�`�揈��

	void CreateExplosionEffect(VECTOR position);	//�����G�t�F�N�g�̐���

private:
	EffectManager(const EffectManager&);		//�R�s�[�R���X�g���N�^

	string InputPath(string folderPath,
					 string effectPath);		//�G�t�F�N�g�p�X�̓���


	EffectBase* effect[EFFECT_AMOUNT];			//�G�t�F�N�g�i�[�p


	//�G�t�F�N�g
	const string EFFECT_FOLDER_PATH;		//Effect�t�H���_�܂ł̃p�X
	const string EXPLOSION_EFFECT_PATH;		//�����G�t�F�N�g�̃p�X

	//�G�t�F�N�g�̃T�C�Y
	const float  EXPLOSION_SIZE;			//�����G�t�F�N�g�̃T�C�Y

};