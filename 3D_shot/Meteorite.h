#pragma once

#include "Dxlib.h"
#include "MeteoriteBase.h"
#include "Math3D.h"
#include "Collision.h"


class Player;

using namespace Math3d;

//覐΂̐F
enum class MeteoriteColor
{
	Nomal,
	BLUE,
	GREEN,
	RED,
};

//覐΃N���X
//MeteoriteBase�N���X���p��
class Meteorite final : public MeteoriteBase
{
public:
	 Meteorite();
	~Meteorite();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void SpeedUp();
	void RedColor();
	void YellowColor();
	void OrangeCollor();
	void Draw();
	
	Sphere GetCollisionSphere() { return collisionSphere; } //�����蔻�苅��Ԃ�

	enum class MeteoriteColor meteoriteColor;

private:
	Meteorite(const Meteorite&);				//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Player* player);		//�ړ�����
	void mUpdate();									//��ԕω�
	
	
	int shadowMapHandle;
	
	Sphere collisionSphere;				//�����蔻�苅

};