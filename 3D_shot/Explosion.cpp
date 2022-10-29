#include "Explosion.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Meteorite.h"


Explosion::Explosion()
	: /*effectHandle(0)*/
	  effectPos_X(0.0f)
	, effectPos_Y(0.0f)
	, effectTime(0)
	, playingEffectHandle(-1)
{
	effect = Effect::Nomal;
}

Explosion::~Explosion()
{
	//�����Ȃ�
}

void Explosion::Initialize()
{
	bi = LoadEffekseerEffect("data/effect/Explosion.efkefc", 30.0f);
	ai = LoadEffekseerEffect("data/effect/Explosion.efkefc", 10.0f);
	/*grBackgroundHandle = LoadGraph(("data/texture/Background.png"));
	grFrontHandle = LoadGraph(("data/texture/Front.png"));*/
}

void Explosion::Finalize()
{
	// �G�t�F�N�g���\�[�X���폜
	DeleteEffekseerEffect(bi);
}

void Explosion::Activate()
{
}

void Explosion::Update(Meteorite* meteorite)
{
	effectPos_X = meteorite->GetPosition().x;
	effectPos_Y = meteorite->GetPosition().y;

	// ����I�ɃG�t�F�N�g���Đ�
	if (effectTime % 1 == 0)
	{
		// �G�t�F�N�g���Đ�
		playingEffectHandle = PlayEffekseer3DEffect(bi);
	}

	// �Đ����̃G�t�F�N�g���ړ�
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos_X, effectPos_Y, 0);

	// ���Ԃ��o��
	effectTime++;
}

void Explosion::Estate(Meteorite* meteorite)
{
	effectPos_X = meteorite->GetPosition().x;
	effectPos_Y = meteorite->GetPosition().y;

	// ����I�ɃG�t�F�N�g���Đ�
	if (effectTime % 1 == 0)
	{
		// �G�t�F�N�g���Đ�
		playingEffectHandle = PlayEffekseer3DEffect(ai);
	}

	// �Đ����̃G�t�F�N�g���ړ�
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos_X, effectPos_Y, 0);

	// ���Ԃ��o��
	effectTime++;
}

void Explosion::Draw()
{
	//DrawGraph(0, 100, grBackgroundHandle, TRUE);

	//// �G�t�F�N�g�̏�ɂ��摜��`��ł���B
	//DrawGraph(0, 100, grFrontHandle, TRUE);

	// �Đ����̃G�t�F�N�g���X�V
	UpdateEffekseer3D();

	// �Đ����̃G�t�F�N�g��`��
	DrawEffekseer3D();
}