#include "Explosion.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Meteorite.h"


Explosion::Explosion()
	: effectHandle(0)
	, effectPos_X(0.0f)
	, effectPos_Y(0.0f)
	, effectPos_Z(0.0f)
	, effectTime(0)
	, playingEffectHandle(-1)
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
	effectHandle = LoadEffekseerEffect("data/effect/Explosion.efkefc", 15.0f);
	explosionSE = LoadSoundMem("data/sound/ExplosionSE.mp3");
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