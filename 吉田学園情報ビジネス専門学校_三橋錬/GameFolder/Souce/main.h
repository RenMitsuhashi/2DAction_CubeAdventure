//=============================================================================
//
// ���C������ [main.h]
// Author : �O���B
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION (0x0800)
#define _USE_MATH_DEFINES

// �O���錾
class CRenderer;
class CScene;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
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
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")			// �`��ɕK�v
#pragma comment(lib,"d3dx9.lib")		// [d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		// DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"dinput8.lib")		// ���͏����ɕK�v
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH (1620)				// �E�B���h�E�̕�
#define SCREEN_HEIGHT (900)				// �E�B���h�E�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int GetFPS();
D3DXVECTOR3 GetMouse();

#endif