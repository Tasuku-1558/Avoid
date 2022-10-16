#pragma once


//�V�[���̎��
enum class SceneType
{
	TITLE,
	PLAY,
	RESULT
};

class SceneBase
{
public:
	SceneBase(SceneType sceneType):NowSceneType(sceneType){ /*�����Ȃ�*/} //�R���X�g���N�^
	virtual ~SceneBase(){/*�����Ȃ�*/} //�f�X�g���N�^

	virtual void Initialize() = 0;
	virtual SceneType Update(float deltaTime) = 0;
	virtual void Draw() = 0;

protected:
	SceneType NowSceneType;
};