#include "Explosion.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"


const string Explosion::EFFECT_FOLDER_PATH = "data/effect/";		//effect�t�H���_�܂ł̃p�X
const string Explosion::EXPLOSION_PATH	   = "Explosion.efkefc";	//�����G�t�F�N�g�̃p�X
const string Explosion::SOUND_FOLDER_PATH  = "data/sound/";			//sound�t�H���_�܂ł̃p�X
const string Explosion::EXPLOSION_SE_PATH  = "ExplosionSE.mp3";		//����SE�̃p�X


/// <summary>
/// �R���X�g���N�^
/// </summary>
Explosion::Explosion()
	: effectHandle(0)
	, effectTime(0)
	, playingEffectHandle(0)
	, explosionSE(0)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Explosion::~Explosion()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Explosion::Initialize()
{
	string failePath = EFFECT_FOLDER_PATH + EXPLOSION_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), 15.0f);

	failePath = SOUND_FOLDER_PATH + EXPLOSION_SE_PATH;
	explosionSE = LoadSoundMem(failePath.c_str());
}

/// <summary>
/// �I������
/// </summary>
void Explosion::Finalize()
{
	// �G�t�F�N�g���\�[�X���폜
	DeleteEffekseerEffect(effectHandle);

	// �T�E���h���\�[�X���폜
	InitSoundMem();
}

/// <summary>
/// ����������
/// </summary>
void Explosion::Activate()
{
	// �G�t�F�N�g���~����
	StopEffekseer3DEffect(playingEffectHandle);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="effectPos"></param>
void Explosion::Update(VECTOR effectPos)
{
	// ����I�ɃG�t�F�N�g���Đ�
	if (effectTime % 1 == 0)
	{
		// �G�t�F�N�g���Đ�
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// ����SE���Đ�
		PlaySoundMem(explosionSE, DX_PLAYTYPE_BACK);
	}

	// �Đ����̃G�t�F�N�g���ړ�
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos.x, effectPos.y, effectPos.z);

	// ���Ԃ��o��
	effectTime++;
}

/// <summary>
/// �`�揈��
/// </summary>
void Explosion::Draw()
{
	// �Đ����̃G�t�F�N�g���X�V
	UpdateEffekseer3D();

	// �Đ����̃G�t�F�N�g��`��
	DrawEffekseer3D();
}