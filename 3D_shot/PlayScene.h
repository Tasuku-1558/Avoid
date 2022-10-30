#pragma once

#include "SceneBase.h"

class Camera;
class Player;
class Meteorite;
class MeteoriteManager;
class HitChecker;
class Explosion;
class Evaluation;

class PlayScene final : public SceneBase
{
public:
	 PlayScene(SceneManager* const sceneManager);
	~PlayScene()override;

	void Initialize() override;
	void Finalize()override;
	void Activate()override;
	void Update(float deltaTime)override;
	void Draw() override;

	
private:
	Camera* camera;
	Player* player;
	Meteorite* meteorite[54] = { nullptr };
	MeteoriteManager* meteoriteManager;
	HitChecker* hitchecker;
	Explosion* explosion;
	Evaluation* evaluation;
	
	int  startTime;				//�N������
	int  nowTime;				//���݂̎���
	int  countDown;				//��������
	bool meteoritePopFlag;		//覐΂̏o���t���O
	int  gameBackGround;		//�Q�[����ʔw�i
	int  targetScore;			//�ڕW�X�R�A
	int  score;					//�l���X�R�A
	
	//�f�o�b�N�p
	int x;
	int y;
	double Direction = 0.0f;

	
	//�ÓI�萔
	static const int GAMETIME;	//�Q�[������
};