#include "ObjectBase.h"


ObjectBase::ObjectBase()
    : Position()
    , Dir()
    , ModelHandle(-1)
{
    //処理なし
}

ObjectBase::~ObjectBase()
{
    //処理なし
}

void ObjectBase::Draw()
{
    //処理なし
}

//ゲッター関数群
const VECTOR& ObjectBase::GetPosition() const
{
    return Position;
}

const VECTOR& ObjectBase::GetDir() const
{
    return Dir;
}
