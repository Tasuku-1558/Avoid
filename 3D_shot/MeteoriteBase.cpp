#include "MeteoriteBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
MeteoriteBase::MeteoriteBase()
	: randomDirection(0)
	, speed(0.0f)
	, popFlag(true)
	, playerPosition()
	, rotate()
	, rotateSpeed()
	, RANGE_DIRECTION(2)
	, SPEED(1500.0f)
	, SPEED_UP(2500.0f)
	, RANDOM_POSITION({ (float)GetRand(400), (float)GetRand(400), 1600.0f })
	, SIZE({ 0.3f, 0.3f, 0.3f })
	, DIRECTION({ 0.0f, 0.0f, -1.0f })
	, ROTATE_SPEED({ GetRandf(0.0f, 0.2f), GetRandf(0.0f, 0.2f), GetRandf(0.0f, 0.2f) })
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MeteoriteBase::~MeteoriteBase()
{
	//�����Ȃ�
}