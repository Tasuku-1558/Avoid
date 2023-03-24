#pragma once

#include "SceneBase.h"
#include <string>

using namespace std;

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene final : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	SceneType Update(float deltaTime)override;		//�X�V����
	void Draw()override;							//�`�揈��
	
private:

	TitleScene(const TitleScene&);		//�R�s�[�R���X�g���N�^

	void Initialize()override;			//����������
	void Activate()override;			//����������
	void Blink();						//�����̓_��

	string InputPath(string folderPath,
					 string path);		//�p�X�����

	//�^�C�g���̏��
	enum class SelectState
	{
		START,	//�Q�[�����n�߂�
		EXIT,	//�Q�[�����I������
	};

	SelectState selectState;			//�^�C�g���̏��
	int titleMovie;						//�^�C�g������̊i�[�p
	int titleName;						//�^�C�g�����̉摜�i�[�p
	int titleUi;						//�v���C�V�[���֑J�ڃL�[��UI�i�[�p
	int alpha;							//���ߓx
	int inc;
	float frame;						//�t���[����


	//�萔
	const string VIDEO_FOLDER_PATH;		//Video�t�H���_�܂ł̃p�X
	const string IMAGE_FOLDER_PATH;		//Image�t�H���_�܂ł̃p�X
	const string PLAY_VIDEO_PATH;		//�^�C�g������̃p�X
	const string TITLENAME_PATH;		//�^�C�g�����̉摜�̃p�X
	const string TITLE_UI_PATH;			//�v���C�V�[���֑J�ڃL�[��UI�̃p�X
	const int	 MAX_ALPHA;				//�ő哧�ߓx
	const int	 PLAY_POSITION;			//�^�C�g������̍Đ��ʒu

};