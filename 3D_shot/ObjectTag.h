#pragma once

#include <vector>


//ゲーム内アクター・当たり判定の種類別タグ
enum class ObjectTag : unsigned char
{
	Player,
	Meteorite,
};

constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Player,
	ObjectTag::Meteorite,
};