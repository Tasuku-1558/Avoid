#pragma once

class SceneBase;


class SceneManager final
{
public:

	//�V�[�����
	enum Scene
	{
		TITLE = 0,		//�^�C�g�����
		PLAY,			//�Q�[�����
		RESULT,			//���U���g���
		END				//�I���ƃV�[����
	};

	SceneManager();
   ~SceneManager();

   void Initialize();
   void Finalize();
   void Update(float deltaTime);
   void Draw();

   void  SetNextScene(Scene next);		//���̃V�[�����Z�b�g
   Scene GetNowScene();					//���̃V�[�����擾
   Scene GetNextScene();				//���̃V�[�����擾

private:

	SceneManager(const SceneManager&);	//�R�s�[�R���X�g���N�^

	SceneBase* eachScene[Scene::END];	//�e�V�[���̃C���X�^���X
	SceneBase* nowPointer;				//���̃V�[���|�C���^
	Scene	   nowScene;				//���̃V�[��
	Scene	   nextScene;				//���̃V�[��

	void	  ChangeScene();			//�V�[���̕ύX
};