#pragma once

#include <vector>


//�Q�[�����A�N�^�[�E�����蔻��̎�ޕʃ^�O
enum class ObjectTag : unsigned char
{
	Player,
	Meteorite,
	HitChecker,
};

constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Player,
	ObjectTag::Meteorite,
	ObjectTag::HitChecker,
};