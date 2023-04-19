#pragma once

#include "DxLib.h"

const int SCREEN_WIDTH  = 1920;						//ウィンドウの幅
const int SCREEN_HEIGHT = 1080;						//ウィンドウの高さ
const int COLOR_BIT     = 32;						//カラービット数
const int MAX_PARTICLE_NUMBER = 2200;               //画面に表示する最大パーティクル数

const float WAIT_FRAME_TIME = 16667.0f;				//待機フレーム時間(60fps)
const float SLOW_DELETA_TIME_DIVISION = 3000000.0f;	//低速時のデルタタイムを割る値
const float NOMAL_DELETA_TIME_DIVISION = 1000000.0f;//通常時のデルタタイムを割る値

const bool IS_WINDOW_MODE = true;					//ウィンドウモードにするか

const VECTOR ZERO_VECTOR  = { 0.0f, 0.0f, 0.0f };	//ゼロベクトル

const VECTOR LIGHT_DIRECTION = { 0.0f, -0.5f, 0.5f };   //シャドウマップが想定するライトの方向

const VECTOR SHADOWMAP_MINPOSITION = { -2000.0f, -1.0f, -2000.0f }; //影を描画する範囲の座標の最小値
const VECTOR SHADOUMAP_MAXPOSITION = { 2000.0f, 1000.0f, 2500.0f }; //影を描画する範囲の座標の最大値