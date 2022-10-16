#pragma once

#include "SceneBase.h"

class PlayScene final : public SceneBase
{
public:
	 PlayScene();
	~PlayScene()override;

	void Initialize() override;
	SceneType Update(float deltaTime) override;
	void Draw() override;
	
	int GetScore() { return Score; }

private:
	class Camera* camera;
	class Player* player;
	class Meteorite* meteorite[20] = { nullptr };/*[Meteorite::METEORITE_ARRAY_NUMBER10] = { nullptr };*/
	class HitChecker* hitchecker;
	
	int  StartTime;				//�N������
	int  NowTime;				//���݂̎���
	int  CountDown;				//��������
	bool MeteoritePopFlag;		//覐΂̏o���t���O

	int  GameBackground;		//�Q�[����ʔw�i

	//�f�o�b�N�p
	int x;
	int y;
	double Direction = 0.0f;

	int  TargetScore;			//�ڕW�X�R�A
	int  Score;					//�l���X�R�A
	
	
	//�ÓI�萔
	static const int GameTime;	//�Q�[������
};