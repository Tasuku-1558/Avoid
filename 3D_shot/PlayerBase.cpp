#include "PlayerBase.h"


const float PlayerBase::SIZE   = 0.4f;		//ƒ‚ƒfƒ‹”{—¦
const float PlayerBase::SPEED  = 400.0f;	//ˆÚ“®‘¬“x
const float PlayerBase::RADIUS = 41.0f;		//”¼Œa‚Ì”ÍˆÍ


PlayerBase::PlayerBase(ObjectTag tag)
	: Tag(tag)
	, inputDirection()
	, inputFlag(false)
	, UP()
	, DOWN()
	, LEFT()
	, RIGHT()
{
	//ˆ—‚È‚µ
}

PlayerBase::~PlayerBase()
{
	//ˆ—‚È‚µ
}
