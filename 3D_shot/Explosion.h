#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

/// <summary>
/// �����G�t�F�N�g�N���X
/// </summary>
class Explosion final : public EffectBase
{
public:
	Explosion();
	virtual ~Explosion();

	void Initialize()override;					//����������
	void Finalize()override;					//�I������
	void Activate()override;					//����������
	void Update(VECTOR effectPos)override;		//�X�V����
	void Draw()override;						//�`�揈��

private:
	
	int effectHandle;				//�����G�t�F�N�g�i�[�p
	int explosionSE;				//����SE�i�[�p
	int effectTime;					//�G�t�F�N�g����
	int playingEffectHandle;		//�Đ����̃G�t�F�N�g�̃n���h����������


	//�ÓI�萔
	static const string EFFECT_FOLDER_PATH;		//effect�t�H���_�܂ł̃p�X
	static const string SOUND_FOLDER_PATH;		//sound�t�H���_�܂ł̃p�X
	static const string EXPLOSION_PATH;			//�����G�t�F�N�g�̃p�X
	static const string EXPLOSION_SE_PATH;		//����SE�̃p�X

};