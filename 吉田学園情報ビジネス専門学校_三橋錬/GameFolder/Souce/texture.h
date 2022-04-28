//=============================================================================
//
// テクスチャ [texture.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTexture
{
public:
	enum TexType
	{
		Tex_None = 0,		// テクスチャ無し
		Tex_Test,			// 仮テクスチャ
		Tex_Fade,			// フェード用テクスチャ
		Tex_Number,			// 数字テクスチャ
		Tex_Effect,			// 丸いエフェクトテクスチャ

		Tex_BgTitle,		// タイトルの背景
		Tex_TitleLogo,
		Tex_TitleUIGame,
		Tex_TitleUIBuild,
		Tex_TitleUIQuit,
		Tex_TitleModeSelect,

		Tex_BgGame,			// 背景テクスチャゲーム用
		Tex_Tutorialwasd,
		Tex_Tutorialjump,
		Tex_TutorialGravityReverse,
		Tex_TutorialGravityUpDown,
		Tex_TutorialGoal,

		Tex_GoalLogo,
		Tex_Time,
		Tex_Death,
		Tex_PressEnter,

		Tex_Pause_Resume,
		Tex_Pause_Save,
		Tex_Pause_Title,
		Tex_Pause_Cursor,

		Tex_BgGravity,		// 背景テクスチャ
		Tex_BgReverse,		// 重力反転の背景テクスチャ
		Tex_Planet,			// 惑星
		Tex_BgMax,			// 背景テクスチャの最大

		Tex_NormalBlock,	// ブロックテクスチャ
		Tex_Player,			// プレイヤーテクスチャ

		Tex_Reverse,		// 重力反転のテクスチャ
		Tex_Goal,			// ゴールのテクスチャ
		Tex_Spiny,			// 棘テクスチャ

		Tex_TargetBlock,
		Tex_ObjMax,			// オブジェクトの最大

		Tex_Max,			// テクスチャの最大数
	};

	CTexture();
	~CTexture();

	void Init();	// テクスチャの生成
	void Uninit();	// 終了

	static LPDIRECT3DTEXTURE9 GetTexture(int Type) { return m_pTexture[Type]; }	// テクスチャの割り当て(テクスチャの種類) { return 選んだテクスチャを返す }

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[Tex_Max];	// テクスチャ
};

#endif