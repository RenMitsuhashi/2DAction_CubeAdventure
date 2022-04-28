//=============================================================================
//
// �V�[������ [scene.h]
// Author : �O���B
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene
{
public:
	// �K�w enum��`
	enum PRIORITY
	{
		PRIORITY_NONE = 0,

		PRIORITY_BG,

		// �I�u�W�F�N�g�̔w�i
		PRIORITY_BGOBJECT,

		PRIORITY_BLOCK,
		PRIORITY_REVERSE,
		PRIORITY_SPINY,
		PRIORITY_GOAL,

		PRIORITY_TARGETBLOCK,

		// �L�����N�^�[
		PRIORITY_PLAYER,

		PRIORITY_OBJMAX,

		PRIORITY_CURSOR,
		PRIORITY_EFFECT,

		PRIORITY_UIBG,
		PRIORITY_UI,
		PRIORITY_PAUSE,
		PRIORITY_FADE,
		PRIORITY_MAX
	};

	enum Direction
	{
		DIRECTION_NONE = 0,
		DIRECTION_UP,
		DIRECTION_LEFT,
		DIRECTION_DOWN,
		DIRECTION_RIGHT,
		DIRECTION_MAX
	};

	CScene(int nPriority = PRIORITY_NONE);
	virtual ~CScene();

	virtual HRESULT Init(LPDIRECT3DTEXTURE9 tex) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void UpdateAll();					// �S�Ẵ|���S����Update
	static void DrawAll();						// �S�Ẵ|���S����Draw
	static void ReleaseAll();					// �S�Ẵ|���S����Release

	// �Z�b�^�[
	//*****************************************************************************
	// �|�W�V����
	void SetPos(const D3DXVECTOR3& pos)			{ m_Pos = pos; }
	void SetPosold(const D3DXVECTOR3& pos)		{ m_Posold = pos; }
	void SetstartPos(const D3DXVECTOR3& pos)	{ m_startPos = pos; }

	void ReturnTostartPos(CScene *scene);
	void ReturnTostartPosAll();

	// �ׂ����|�W�V����
	void SetPosX(const float& pos)				{ m_Pos.x = pos; }
	void SetPosY(const float& pos)				{ m_Pos.y = pos; }
	void SetPosZ(const float& pos)				{ m_Pos.z = pos; }

	// �ړ��l
	void SetMove(const D3DXVECTOR3& move)		{ m_Move = move; }
	void SetstartMove(const D3DXVECTOR3& move)	{ m_startMove = move; }

	// �ׂ����ړ��l
	void SetMoveX(const float& move)			{ m_Move.x = move; }
	void SetMoveY(const float& move)			{ m_Move.y = move; }
	void SetMoveZ(const float& move)			{ m_Move.z = move; }

	// �T�C�Y
	void SetSize(const D3DXVECTOR3& size)		{ m_Size = size; }

	// �ׂ����T�C�Y
	void SetSizeX(const float& size) { m_Size.x = size; }
	void SetSizeY(const float& size) { m_Size.y = size; }
	void SetSizeZ(const float& size) { m_Size.z = size; }

	// m_bDeath�֘A
	void SetDeath(bool tf) { m_bDeath = tf; }

	void SetobjType(int num) { m_nObjType = num; }

	void SetColision(CScene *obj, int direction) { m_ColisionObj[direction] = obj; }

	void Setptn(int num) { m_ptn = num; }

	// �u���b�N�p
	//=============================================================================
	void SetTargetPos(D3DXVECTOR3 pos) { m_TargetPos = pos; }
	void SetStopTime(int time) { m_nStopTime = time; }

	// �Q�b�^�[
	//*****************************************************************************
	D3DXVECTOR3 GetPos() const { return m_Pos; }
	D3DXVECTOR3 GetPosold() const { return m_Posold; }
	D3DXVECTOR3 GetstartPos() const { return m_startPos; }

	D3DXVECTOR3 GetMove() const { return m_Move; }
	D3DXVECTOR3 GetstartMove() const { return m_startMove; }

	D3DXVECTOR3 GetSize() const	{ return m_Size; }

	int GetPriority() const { return m_nPriority; }

	// m_bDeath
	bool GetDeath() const { return m_bDeath; }

	CScene *GetTop(int nPriority) const { return m_pTop[nPriority]; }
	CScene *GetNext() const { return m_pNext; }

	int GetobjType() const { return m_nObjType; }

	CScene *GetColision(int direction) const { return m_ColisionObj[direction]; }
	
	// �u���b�N�p
	//=============================================================================
	D3DXVECTOR3 GetTargetPos() const { return m_TargetPos; }
	int GetStopTime() const { return m_nStopTime; }

	static int Sign(float num);

	static void RandomShake(D3DXVECTOR3 shakerand);

	D3DCOLORVALUE GetCol() { return m_col; }
	int GetPtn() { return m_ptn; }

protected:
	void Release(int nPriority);			// ������Release

	void SetCol(D3DCOLORVALUE col)
	{
		m_col.r = col.r;
		m_col.g = col.g;
		m_col.b = col.b;
		m_col.a = col.a;
	}

private:
	static CScene	*m_pTop[PRIORITY_MAX];	// �擪�̃I�u�W�F�N�g
	static CScene	*m_pBot[PRIORITY_MAX];	// �Ō���̃I�u�W�F�N�g

	CScene			*m_pNext;				// ���̃I�u�W�F�N�g
	CScene			*m_pPrev;				// �O�̃I�u�W�F�N�g

	static int		m_nNumAll;				// �I�u�W�F�N�g�̍ő吔(�ǉ����邽�тɑ�������)

	D3DXVECTOR3		m_Pos;					// �|���S���̈ʒu
	D3DXVECTOR3		m_Posold;				// 1f�O�̃|���S���̈ʒu
	D3DXVECTOR3		m_startPos;				// �Q�[���J�n���̃|���S���̈ʒu

	D3DXVECTOR3		m_Move;					// �|���S���̈ړ���
	D3DXVECTOR3		m_startMove;			// �Q�[���J�n���̃|���S���̈ړ���

	D3DXVECTOR3		m_Size;					// �|���S���̃T�C�Y

	int				m_nPriority;			// �I�u�W�F�N�g�̊K�w
	bool			m_bDeath;				// ���S�t���O

	int				m_nObjType;				// �I�u�W�F�N�g�^�C�v

	D3DXVECTOR3		m_vtxMinModel;			// ���f���̍ŏ��l
	D3DXVECTOR3		m_vtxMaxModel;			// ���f���̍ő�l

	CScene			*m_ColisionObj[DIRECTION_MAX];	// �l�����ɉ��炩�̃I�u�W�F�N�g���������Ă��邩

	// �u���b�N�p
	D3DXVECTOR3		m_TargetPos;			// �ړ��ڕW�n�_
	int				m_nStopTime;			// ��~����

	D3DCOLORVALUE	m_col;					// �u���b�N�̐F
	int				m_ptn;					// �u���b�N�̃e�N�X�`���p�^�[��
};

#endif