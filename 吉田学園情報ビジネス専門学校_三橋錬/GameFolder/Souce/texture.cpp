//=============================================================================
//
// テクスチャ [texture.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9	CTexture::m_pTexture[] = {};

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 無し
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\white.png",
		&m_pTexture[Tex_None]);

	// 仮テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\無題.png",
		&m_pTexture[Tex_Test]);

	// フェードテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\white.png",
		&m_pTexture[Tex_Fade]);

	// 数字テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\number.png",
		&m_pTexture[Tex_Number]);

	// 丸いエフェクトテクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\effect000.png",
		&m_pTexture[Tex_Effect]);

	// 背景テクスチャタイトル用の読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\bg.png",
		&m_pTexture[Tex_BgTitle]);

	// ロゴの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\logo.png",
		&m_pTexture[Tex_TitleLogo]);

	// ゲームシーン遷移用テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\game.png",
		&m_pTexture[Tex_TitleUIGame]);

	// ビルダーシーン遷移用テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\build.png",
		&m_pTexture[Tex_TitleUIBuild]);

	// ゲーム終了用テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\quit.png",
		&m_pTexture[Tex_TitleUIQuit]);

	// シーン選択用テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\arrow.png",
		&m_pTexture[Tex_TitleModeSelect]);

	// 背景テクスチャゲーム用の読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\black.png",
		&m_pTexture[Tex_BgGame]);

	// 背景テクスチャゲーム用の読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\tutorial_wasd.png",
		&m_pTexture[Tex_Tutorialwasd]);

	// チュートリアルの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\tutorial_jump.png",
		&m_pTexture[Tex_Tutorialjump]);

	// チュートリアルの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\tutorial_gravity.png",
		&m_pTexture[Tex_TutorialGravityReverse]);

	// チュートリアルの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\tutorial_gravityupdown.png",
		&m_pTexture[Tex_TutorialGravityUpDown]);

	// チュートリアルの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\tutorial_goal.png",
		&m_pTexture[Tex_TutorialGoal]);

	// ロゴの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\stageclear.png",
		&m_pTexture[Tex_GoalLogo]);

	// ロゴの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\time.png",
		&m_pTexture[Tex_Time]);

	// ロゴの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\death.png",
		&m_pTexture[Tex_Death]);

	// ロゴの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\pressenter.png",
		&m_pTexture[Tex_PressEnter]);

	// ロゴの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\pause_resume.png",
		&m_pTexture[Tex_Pause_Resume]);

	// ロゴの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\pause_save.png",
		&m_pTexture[Tex_Pause_Save]);

	// ロゴの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\pause_title.png",
		&m_pTexture[Tex_Pause_Title]);

	// ロゴの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\pause_cursor.png",
		&m_pTexture[Tex_Pause_Cursor]);

	// 背景テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\object\\gravity_bg.png",
		&m_pTexture[Tex_BgGravity]);

	// 重力反転の背景テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\object\\gravityreversebg.png",
		&m_pTexture[Tex_BgReverse]);

	// 背景テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\planet.bmp",
		&m_pTexture[Tex_Planet]);

	// ブロックテクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\white.png",
		&m_pTexture[Tex_NormalBlock]);

	// プレイヤーテクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\player.png",
		&m_pTexture[Tex_Player]);

	// 重力反転テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\object\\gravityreversegage.png",
		&m_pTexture[Tex_Reverse]);

	// ゴールテクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\object\\goal.png",
		&m_pTexture[Tex_Goal]);

	// 棘テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\object\\spiny.png",
		&m_pTexture[Tex_Spiny]);
}

//=============================================================================
// 終了
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < Tex_Max; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}