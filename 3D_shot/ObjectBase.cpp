#include "ObjectBase.h"


ObjectBase::ObjectBase()
    : position()
    , dir()
    , modelHandle(-1)
{
    //処理なし
}

ObjectBase::~ObjectBase()
{
    //処理なし
}

/// <summary>
/// ゲッター関数群
/// </summary>
/// <returns></returns>
const VECTOR& ObjectBase::GetPosition() const
{
    return position;
}

const VECTOR& ObjectBase::GetDir() const
{
    return dir;
}