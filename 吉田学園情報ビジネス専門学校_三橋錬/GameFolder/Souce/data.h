//=============================================================================
//
// �f�[�^ [data.h]
// Author : �O���B
//
//=============================================================================
#ifndef _DATA_H_
#define _DATA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// �N���X��`
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

	// �ړ���
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
	static CManager::MODE m_NowScene;		// ���݂̃V�[��
	static bool m_bNowGame;					// ���݃Q�[�����Ȃ�true�A�z�u����false
	static bool m_bPause;					// ���Ԓ�~
	static bool m_bLive;					// �������Ȃ�false
	static float m_fGravity;				// ���݂̏d�͔{��
	static int m_nDeathCount;				// ���S��
	static const int m_nMaxDeathCount = 99;	// ���S�񐔂̍ő吔
	static int m_nNextStage;				// ���݂̃X�e�[�W
	static int m_nTime;						// �o�ߎ���
	static float m_fMoveQuantity;			// ��ʂ̑��ړ���
};

#endif