#include "ObjectBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
ObjectBase::ObjectBase()
    : position()
    , dir()
    , modelHandle(-1)
{
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
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