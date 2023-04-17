#include "PlayerBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerBase::PlayerBase()
	: lingModel(0)
	, afterImageModelHandle()
	, damageTime(0.0f)
	, inputFlag(false)
	, noDrawFrame(false)
	, inputDirection()
	, rotate()
	, rotateSpeed()
	, pastPosition()
	, UP_RANGE(350)
	, DOWN_RANGE(50)
	, LEFT_RANGE(-410)
	, RIGHT_RANGE(410)
	, AFTER_IMAGE_NUMBER(10)
	, SPEED(400.0f)
	, RADIUS(40.0f)
	, OPACITY(0.05f)
	, MAX_FLASH_TIME(1.0f)
	, INITIAL_DAMAGE_TIME(0.0f)
	, MAX_INPUT_DIRECTION(1.0f)
	, POSITION({ 0.0f, 200.0f, 150.0f })
	, SIZE({ 0.4f, 0.4f, 0.4f })
	, UP({ 0, 1, 0 })
	, DOWN({ 0,-1, 0 })
	, LEFT({ -1, 0, 0 })
	, RIGHT({ 1, 0, 0 })
	, LING_ROTATE_SPEED({ 0.0f, 5.0f, 0.0f })
	, LING_SIZE({ -0.5f, -0.5f, -0.5f })
	, AFTER_IMAGE_COLOR(GetColorF(0.0f, 0.0f, 1.0f, 1.0f))
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerBase::~PlayerBase()
{
	//処理なし
}