#include "ObjectBase.h"


ObjectBase::ObjectBase()
    : position()
    , dir()
    , modelHandle(-1)
{
    //�����Ȃ�
}

ObjectBase::~ObjectBase()
{
    //�����Ȃ�
}

//void ObjectBase::Draw()
//{
//    //�����Ȃ�
//}

//�Q�b�^�[�֐��Q
const VECTOR& ObjectBase::GetPosition() const
{
    return position;
}

const VECTOR& ObjectBase::GetDir() const
{
    return dir;
}
