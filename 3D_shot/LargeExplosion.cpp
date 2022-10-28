#include "LargeExplosion.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Meteorite.h"


LargeExplosion::LargeExplosion()
	: effectHandle(0)
	, effectPos_X(0.0f)
	, effectPos_Y(0.0f)
	, effectTime(0)
	, playingEffectHandle(-1)
{
	effect = Effect::Nomal;
}

LargeExplosion::~LargeExplosion()
{
	//�����Ȃ�
}

void LargeExplosion::Initialize()
{
	effectHandle = LoadEffekseerEffect("data/effect/LargeExplosion.efkefc", 30.0f);
	/*grBackgroundHandle = LoadGraph(("data/texture/Background.png"));
	grFrontHandle = LoadGraph(("data/texture/Front.png"));*/
}

void LargeExplosion::Finalize()
{
	// �G�t�F�N�g���\�[�X���폜
	DeleteEffekseerEffect(effectHandle);
}

void LargeExplosion::Activate()
{
}

void LargeExplosion::Update(Meteorite* meteorite)
{
	effectPos_X = meteorite->GetPosition().x;
	effectPos_Y = meteorite->GetPosition().y;

	// ����I�ɃG�t�F�N�g���Đ�
	if (effectTime % 1 == 0)
	{
		// �G�t�F�N�g���Đ�
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
	}

	// �Đ����̃G�t�F�N�g���ړ�
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos_X, effectPos_Y, 0);

	// ���Ԃ��o��
	effectTime++;
}

void LargeExplosion::Estate()
{
	switch (effect)
	{
	case Effect::Excellent:
		break;
	case Effect::Great:
		break;
	case Effect::Good:
		break;
	default:
		break;
	}
}

void LargeExplosion::Draw()
{
	//DrawGraph(0, 100, grBackgroundHandle, TRUE);

	//// �G�t�F�N�g�̏�ɂ��摜��`��ł���B
	//DrawGraph(0, 100, grFrontHandle, TRUE);

	// �Đ����̃G�t�F�N�g���X�V
	UpdateEffekseer3D();

	// �Đ����̃G�t�F�N�g��`��
	DrawEffekseer3D();
}