#include "ObjectBase.h"


ObjectBase::ObjectBase()
    : Position()
    , Dir()
    , ModelHandle(-1)
{
    //�����Ȃ�
}

ObjectBase::~ObjectBase()
{
    //�����Ȃ�
}

void ObjectBase::Draw()
{
    //�����Ȃ�
}

//�Q�b�^�[�֐��Q
const VECTOR& ObjectBase::GetPosition() const
{
    return Position;
}

const VECTOR& ObjectBase::GetDir() const
{
    return Dir;
}
