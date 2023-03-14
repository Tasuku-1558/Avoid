#pragma once

#include "DxLib.h"

//-----------------------------------------------------------------------------
// 共通の定数などの宣言
//-----------------------------------------------------------------------------
const bool IS_WINDOW_MODE = true;					//ウィンドウモードにするか

const int  SCREEN_WIDTH   = 1920;					//ウィンドウの幅
const int  SCREEN_HEIGHT  = 1080;					//ウィンドウの高さ
const int  COLOR_BIT      = 32;                     //カラービット数

const VECTOR ZERO_VECTOR  = { 0.0f, 0.0f, 0.0f };	//ゼロベクトル

//シャドウマップのサイズ
const int  SHADOWMAP_SIZE_X = 1024;
const int  SHADOWMAP_SIZE_Y = 1024;

const VECTOR LIGHT_DIRECTION = { 0.0f, -0.5f, 0.5f };   //シャドウマップが想定するライトの方向

const VECTOR SHADOWMAP_MINPOSITION = { -1000.0f, -1.0f, -1000.0f }; //影を描画する範囲の座標の最小値
const VECTOR SHADOUMAP_MAXPOSITION = { 1000.0f, 1000.0f, 2500.0f }; //影を描画する範囲の座標の最大値


//インスタンスをdeleteしてNULLを入れる
template <typename T>
inline void SafeDelete(T * &p)
{
    delete (p);
    (p) = nullptr;
}