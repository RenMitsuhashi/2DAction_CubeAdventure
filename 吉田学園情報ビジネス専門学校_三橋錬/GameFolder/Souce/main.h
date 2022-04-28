//=============================================================================
//
// メイン処理 [main.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION (0x0800)
#define _USE_MATH_DEFINES

// 前方宣言
class CRenderer;
class CScene;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <windows.h>
#include <windowsx.h>
#include "d3dx9.h"
#include "dinput.h"
#include "xaudio2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <random>

using namespace std;

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")			// 描画に必要
#pragma comment(lib,"d3dx9.lib")		// [d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		// DirectXコンポーネント使用に必要
#pragma comment(lib,"dinput8.lib")		// 入力処理に必要
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH (1620)				// ウィンドウの幅
#define SCREEN_HEIGHT (900)				// ウィンドウの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int GetFPS();
D3DXVECTOR3 GetMouse();

#endif