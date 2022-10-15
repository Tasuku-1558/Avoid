#pragma once

#include "SceneBase.h"

class PlayScene final : public SceneBase
{
public:
	PlayScene();
	~PlayScene()override;

	void Initialize()override;
	SceneType Update(float deltaTime)override;
	void Draw()override;
	
private:
	class Camera* camera;
	class Player* player;
	class Meteorite* meteorite[10] = { nullptr };/*[Meteorite::METEORITE_ARRAY_NUMBER10] = { nullptr };*/
	
	int StartTime;				//�N������
	int NowTime;				//���݂̎���
	int CountDown;				//��������
	bool MeteoritePopFlag;		//覐΂̏o���t���O

	int GameBackground;			//�Q�[���w�i

	int x;
	int y;
	double Direction = 0.0f;

	int TargetScore = 0;			//�ڕW�X�R�A
	int Score;
	
	
	//�ÓI�萔
	static const int GameTime;	//�Q�[������
};