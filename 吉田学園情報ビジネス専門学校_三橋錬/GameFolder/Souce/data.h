//=============================================================================
//
// データ [data.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _DATA_H_
#define _DATA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CData
{
public:
	enum STAGE
	{
		Stage_Tutorial = 0,
		Stage_01,
		Stage_Build,
		Stage_Max
	};

	CData();
	~CData();

	static void DataReset();

	static void SetNowGame(bool tf)
	{
		m_bNowGame = tf;
	}

	static void ChangeNowGame()
	{
		m_bNowGame = !m_bNowGame;
	}

	static bool GetNowGame() { return m_bNowGame; }

	static void SetPause(bool tf)		{ m_bPause = tf; }
	static void ChangePause()			{ m_bPause = !m_bPause; }
	static bool GetPause()				{ return m_bPause; }

	static void SetLive(bool tf)		{ m_bLive = tf; }
	static void ChangeLive()			{ m_bLive = !m_bLive; }
	static bool GetLive()				{ return m_bLive; }

	static void SetGravity(float num)	{ m_fGravity = num; }
	static void MoveGravity(float move) { m_fGravity += move; }
	static float GetGravity()			{ return m_fGravity; }

	static void SetTime(int num)		{ m_nTime = num; }
	static void AddTime()				{ m_nTime++; }
	static int GetTime()				{ return m_nTime; }

	// 移動量
	static void ZeroMoveQuantity() { m_fMoveQuantity = 0.0f; }
	static void MoveQuantity(float move) { m_fMoveQuantity += move; }
	static float GetMoveQuantity() { return m_fMoveQuantity; }

	static void SetNowScene(CManager::MODE scene) { m_NowScene = scene; }
	static CManager::MODE GetNowScene() { return m_NowScene; }

	static void SetDeathCount(int num)
	{
		m_nDeathCount = num;

		if (m_nDeathCount > m_nMaxDeathCount)
		{
			m_nDeathCount = m_nMaxDeathCount;
		}
	}

	static void AddDeathCount()
	{
		m_nDeathCount++;

		if (m_nDeathCount > m_nMaxDeathCount)
		{
			m_nDeathCount = m_nMaxDeathCount;
		}
	}

	static int GetDeathCount()			{ return m_nDeathCount; }

	static void SetNextStage(int num)	{ m_nNextStage = num; }
	static void AddNextStage()			{ m_nNextStage++; }
	static int GetNextStage()			{ return m_nNextStage; }

private:
	static CManager::MODE m_NowScene;		// 現在のシーン
	static bool m_bNowGame;					// 現在ゲーム中ならtrue、配置中はfalse
	static bool m_bPause;					// 時間停止
	static bool m_bLive;					// 生存中ならfalse
	static float m_fGravity;				// 現在の重力倍率
	static int m_nDeathCount;				// 死亡回数
	static const int m_nMaxDeathCount = 99;	// 死亡回数の最大数
	static int m_nNextStage;				// 現在のステージ
	static int m_nTime;						// 経過時間
	static float m_fMoveQuantity;			// 画面の総移動量
};

#endif