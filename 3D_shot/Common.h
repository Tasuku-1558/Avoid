#pragma once

//--------------------------------------------------
// 共通の定数などの宣言
//--------------------------------------------------
static const bool IS_WINDOW_MODE = true;			//ウィンドウモードにするか

static const int  SCREEN_WIDTH   = 1920;			//ウィンドウの幅
static const int  SCREEN_HEIGHT  = 1080;			//ウィンドウの高さ

static const VECTOR ZERO_VECTOR = { 0.0f, 0.0f, 0.0f };	//ゼロベクトル

//後で消す
// ラインを描く範囲
#define LINE_AREA_SIZE		10000.0f

// ラインの数
#define LINE_NUM			50