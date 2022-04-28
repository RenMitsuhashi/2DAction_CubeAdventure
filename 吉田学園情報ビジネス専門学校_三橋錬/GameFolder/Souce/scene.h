//=============================================================================
//
// シーン処理 [scene.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene
{
public:
	// 階層 enum定義
	enum PRIORITY
	{
		PRIORITY_NONE = 0,

		PRIORITY_BG,

		// オブジェクトの背景
		PRIORITY_BGOBJECT,

		PRIORITY_BLOCK,
		PRIORITY_REVERSE,
		PRIORITY_SPINY,
		PRIORITY_GOAL,

		PRIORITY_TARGETBLOCK,

		// キャラクター
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

	static void UpdateAll();					// 全てのポリゴンをUpdate
	static void DrawAll();						// 全てのポリゴンをDraw
	static void ReleaseAll();					// 全てのポリゴンをRelease

	// セッター
	//*****************************************************************************
	// ポジション
	void SetPos(const D3DXVECTOR3& pos)			{ m_Pos = pos; }
	void SetPosold(const D3DXVECTOR3& pos)		{ m_Posold = pos; }
	void SetstartPos(const D3DXVECTOR3& pos)	{ m_startPos = pos; }

	void ReturnTostartPos(CScene *scene);
	void ReturnTostartPosAll();

	// 細かいポジション
	void SetPosX(const float& pos)				{ m_Pos.x = pos; }
	void SetPosY(const float& pos)				{ m_Pos.y = pos; }
	void SetPosZ(const float& pos)				{ m_Pos.z = pos; }

	// 移動値
	void SetMove(const D3DXVECTOR3& move)		{ m_Move = move; }
	void SetstartMove(const D3DXVECTOR3& move)	{ m_startMove = move; }

	// 細かい移動値
	void SetMoveX(const float& move)			{ m_Move.x = move; }
	void SetMoveY(const float& move)			{ m_Move.y = move; }
	void SetMoveZ(const float& move)			{ m_Move.z = move; }

	// サイズ
	void SetSize(const D3DXVECTOR3& size)		{ m_Size = size; }

	// 細かいサイズ
	void SetSizeX(const float& size) { m_Size.x = size; }
	void SetSizeY(const float& size) { m_Size.y = size; }
	void SetSizeZ(const float& size) { m_Size.z = size; }

	// m_bDeath関連
	void SetDeath(bool tf) { m_bDeath = tf; }

	void SetobjType(int num) { m_nObjType = num; }

	void SetColision(CScene *obj, int direction) { m_ColisionObj[direction] = obj; }

	void Setptn(int num) { m_ptn = num; }

	// ブロック用
	//=============================================================================
	void SetTargetPos(D3DXVECTOR3 pos) { m_TargetPos = pos; }
	void SetStopTime(int time) { m_nStopTime = time; }

	// ゲッター
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
	
	// ブロック用
	//=============================================================================
	D3DXVECTOR3 GetTargetPos() const { return m_TargetPos; }
	int GetStopTime() const { return m_nStopTime; }

	static int Sign(float num);

	static void RandomShake(D3DXVECTOR3 shakerand);

	D3DCOLORVALUE GetCol() { return m_col; }
	int GetPtn() { return m_ptn; }

protected:
	void Release(int nPriority);			// 自分をRelease

	void SetCol(D3DCOLORVALUE col)
	{
		m_col.r = col.r;
		m_col.g = col.g;
		m_col.b = col.b;
		m_col.a = col.a;
	}

private:
	static CScene	*m_pTop[PRIORITY_MAX];	// 先頭のオブジェクト
	static CScene	*m_pBot[PRIORITY_MAX];	// 最後尾のオブジェクト

	CScene			*m_pNext;				// 次のオブジェクト
	CScene			*m_pPrev;				// 前のオブジェクト

	static int		m_nNumAll;				// オブジェクトの最大数(追加するたびに増加する)

	D3DXVECTOR3		m_Pos;					// ポリゴンの位置
	D3DXVECTOR3		m_Posold;				// 1f前のポリゴンの位置
	D3DXVECTOR3		m_startPos;				// ゲーム開始時のポリゴンの位置

	D3DXVECTOR3		m_Move;					// ポリゴンの移動量
	D3DXVECTOR3		m_startMove;			// ゲーム開始時のポリゴンの移動量

	D3DXVECTOR3		m_Size;					// ポリゴンのサイズ

	int				m_nPriority;			// オブジェクトの階層
	bool			m_bDeath;				// 死亡フラグ

	int				m_nObjType;				// オブジェクトタイプ

	D3DXVECTOR3		m_vtxMinModel;			// モデルの最小値
	D3DXVECTOR3		m_vtxMaxModel;			// モデルの最大値

	CScene			*m_ColisionObj[DIRECTION_MAX];	// 四方向に何らかのオブジェクトが当たっているか

	// ブロック用
	D3DXVECTOR3		m_TargetPos;			// 移動目標地点
	int				m_nStopTime;			// 停止時間

	D3DCOLORVALUE	m_col;					// ブロックの色
	int				m_ptn;					// ブロックのテクスチャパターン
};

#endif