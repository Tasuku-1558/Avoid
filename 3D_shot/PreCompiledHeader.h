#pragma once

#include "DxLib.h"

const int SCREEN_WIDTH  = 1920;						//�E�B���h�E�̕�
const int SCREEN_HEIGHT = 1080;						//�E�B���h�E�̍���
const int COLOR_BIT     = 32;						//�J���[�r�b�g��
const int MAX_PARTICLE_NUMBER = 2200;               //��ʂɕ\������ő�p�[�e�B�N����

const float WAIT_FRAME_TIME = 16667.0f;				//�ҋ@�t���[������(60fps)
const float SLOW_DELETA_TIME_DIVISION = 3000000.0f;	//�ᑬ���̃f���^�^�C��������l
const float NOMAL_DELETA_TIME_DIVISION = 1000000.0f;//�ʏ펞�̃f���^�^�C��������l

const bool IS_WINDOW_MODE = true;					//�E�B���h�E���[�h�ɂ��邩

const VECTOR ZERO_VECTOR  = { 0.0f, 0.0f, 0.0f };	//�[���x�N�g��

const VECTOR LIGHT_DIRECTION = { 0.0f, -0.5f, 0.5f };   //�V���h�E�}�b�v���z�肷�郉�C�g�̕���

const VECTOR SHADOWMAP_MINPOSITION = { -2000.0f, -1.0f, -2000.0f }; //�e��`�悷��͈͂̍��W�̍ŏ��l
const VECTOR SHADOUMAP_MAXPOSITION = { 2000.0f, 1000.0f, 2500.0f }; //�e��`�悷��͈͂̍��W�̍ő�l