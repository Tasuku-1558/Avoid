#include "Explosion.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Meteorite.h"


const string Explosion::EFFECT_FOLDER_PATH = "data/effect/";		//effect�t�H���_�܂ł̃p�X
const string Explosion::EXPLOSION_PATH	   = "Explosion.efkefc";	//�����G�t�F�N�g�̃p�X
const string Explosion::SOUND_FOLDER_PATH  = "data/sound/";			//sound�t�H���_�܂ł̃p�X
const string Explosion::EXPLOSION_SE_PATH  = "ExplosionSE.mp3";		//����SE�̃p�X

Explosion::Explosion()
	: effectHandle(0)
	, effectPos_X(0.0f)
	, effectPos_Y(0.0f)
	, effectPos_Z(0.0f)
	, effectTime(0)
	, playingEffectHandle(0)
	, explosionSE(0)
{
	//�����Ȃ�
}

Explosion::~Explosion()
{
	//�����Ȃ�
}

void Explosion::Initialize()
{
	string failePath = EFFECT_FOLDER_PATH + EXPLOSION_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), 15.0f);

	failePath = SOUND_FOLDER_PATH + EXPLOSION_SE_PATH;
	explosionSE = LoadSoundMem(failePath.c_str());
}

void Explosion::Finalize()
{
	// �G�t�F�N�g���\�[�X���폜
	DeleteEffekseerEffect(effectHandle);

	// �T�E���h���\�[�X���폜
	InitSoundMem();
}

void Explosion::Activate()
{
	// �G�t�F�N�g���~����
	StopEffekseer3DEffect(playingEffectHandle);
}

void Explosion::Update(Meteorite* meteorite)
{
	effectPos_X = meteorite->GetPosition().x;
	effectPos_Y = meteorite->GetPosition().y;
	effectPos_Z = meteorite->GetPosition().z;

	// ����I�ɃG�t�F�N�g���Đ�
	if (effectTime % 1 == 0)
	{
		// �G�t�F�N�g���Đ�
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// ����SE���Đ�
		PlaySoundMem(explosionSE, DX_PLAYTYPE_BACK);
	}

	// �Đ����̃G�t�F�N�g���ړ�
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos_X, effectPos_Y, effectPos_Z);

	// ���Ԃ��o��
	effectTime++;
}

void Explosion::Draw()
{
	// �Đ����̃G�t�F�N�g���X�V
	UpdateEffekseer3D();

	// �Đ����̃G�t�F�N�g��`��
	DrawEffekseer3D();
}