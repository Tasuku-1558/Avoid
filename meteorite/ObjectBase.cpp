#include "ObjectBase.h"


ObjectBase::ObjectBase()
    : Position()
    , Dir()
    , ModelHandle(-1)
{
    //ˆ—‚È‚µ
}

ObjectBase::~ObjectBase()
{
    //ˆ—‚È‚µ
}

void ObjectBase::Draw()
{
    //ˆ—‚È‚µ
}

//ƒQƒbƒ^[ŠÖ”ŒQ
const VECTOR& ObjectBase::GetPosition() const
{
    return Position;
}

const VECTOR& ObjectBase::GetDir() const
{
    return Dir;
}
