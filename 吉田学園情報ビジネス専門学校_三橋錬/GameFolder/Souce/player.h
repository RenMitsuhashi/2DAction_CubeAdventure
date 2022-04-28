//=============================================================================
//
// �v���C���[ [player.h]
// Author : �O���B
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define JUMP_HEIGHT (12.0f)
#define EFFECT_MAX (256)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CCursor;
class CUIBg;
class CEffect;
class CDeathCount;
class CTime;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "character.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CCharacter
{
public:
	enum PlayerType
	{
		Player_Normal,
		Player_Left,
		Player_Right = -1,
		Player_Max
	};

	enum GoalEffect
	{
		Goal_Display = 0,
		Goal_Shake,
		Goal_TimeDisplay,
		Goal_DeathCountDisplay,
		Goal_PressEnterDisplay,
		Goal_Max
	};

	enum GoalEffectTexture
	{
		StageClear = 0,
		ClearTimeLogo,
		DeathCountLogo,
		PressEnterLogo,
		Texture_Max
	};

	enum GoalEffectNumber
	{
		ClearTime,
		DeathCount,
		Number_Max
	};

	CPlayer(CScene::PRIORITY nPriority = PRIORITY_PLAYER);
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

	void SetDeath(bool tf) { m_bDeath = tf; }
	void ReverseDeath() { m_bDeath = !m_bDeath; }
	bool GetDeath() { return m_bDeath; }

	static float GetMaxGrav() { return m_fMaxGrav; }
	static float GetMinGrav() { return m_fMinGrav; }

	static CEffect *GetDeathEffect(int num)		{ return m_pDeathEffect[num]; }

	void Death();
	void DeathEffectCreate(int num);
	void Reset();

	void Goal();

	static CUIBg		*GetUIBg(int num)		{ return m_pUIBg[num]; }
	static CDeathCount	*GetDeathCount()		{ return m_pDeathCount; }
	static CTime		*GetTime()				{ return m_pTime; }

private:
	const D3DXVECTOR3 m_Speed = D3DXVECTOR3(0.6f, 0.5f, 0.0f);					// �ړ���
	const D3DXVECTOR3 m_SpeedMax = D3DXVECTOR3(m_Speed.x * 10.0f, 15.0f, 0.0f);	// �ړ��ʂ̍ő�l

	bool m_bJump = false;			// �W�����v����

	int m_nType = Player_Normal;	// �v���C���[�̃e�N�X�`���^�C�v
	const float m_fTexMove = 0.2f;	// �e�N�X�`�������炷�x����

	bool m_bDeath = false;			// �����Ă��邩
	float m_fMove = 0.0f;			// ����

	static const float m_fMoveGrav;
	static const float m_fMaxGrav;
	static const float m_fMinGrav;

	int m_nDeathTime = 0;						// �����܂ł̌o�ߎ���
	const int m_nDeathTimeMax = 128;			// �����܂ł̎���

	static const int m_nDeathEffectCnt = 8;

	static CEffect *m_pDeathEffect[m_nDeathEffectCnt];	// ���S���G�t�F�N�g

	CScene *m_pLastStepblock = NULL;			// �Ō�ɓ���ł����u���b�N(���X�n)
	float m_fLastStepGravity;					// ���𓥂�ł������̏d��

	bool m_bGoal = false;						// �S�[������
	int m_nGoalCount = Goal_Display;			// �S�[�����o
	int m_nGoalTime = 0;						// �S�[�����o���̌o�ߎ���

	static CUIBg		*m_pUIBg[Texture_Max];
	static CDeathCount	*m_pDeathCount;
	static CTime		*m_pTime;

	int m_nFrame = 0;
};

#endif