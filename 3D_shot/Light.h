#pragma once

#include "DxLib.h"

/// <summary>
/// ���C�g�N���X
/// </summary>
class Light final
{
public:

	Light();
	virtual ~Light();

	void TitleLight();			//�^�C�g���V�[���p���C�g
	void GameLight();			//�Q�[���V�[���p���C�g

private:
	Light(const Light&);		//�R�s�[�R���X�g���N�^


	//�萔
	const VECTOR TITLE_DIRECTION;	//�^�C�g���V�[���̃��C�g�̕���
	const VECTOR GAME_DIRECTION;	//�Q�[���V�[���̃��C�g�̕���

};