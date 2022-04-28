//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : 
//
//=============================================================================
#include "scene.h"
#include "renderer.h"

CScene *CScene::m_pTop[] = {};
CScene *CScene::m_pBot[] = {};

int CScene::m_nNumAll = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;				// thisを先頭に設定
	}

	else
	{
		m_pBot[nPriority]->m_pNext = this;		// 最後尾オブジェクトのm_pNextをthisに設定
		m_pPrev = m_pBot[nPriority];			// m_pPrevに最後尾オブジェクトを設定
	}

	m_pNext = NULL;								// 自分が最後尾になるのでm_pNextをNULLにする
	m_pBot[nPriority] = this;					// 最後尾オブジェクトをthisに設定

	m_nNumAll++;								// ポリゴンの数を++
	m_nPriority = nPriority;					// 階層を設定

	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nStopTime = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// オブジェクトを全て消す
//=============================================================================
void CScene::ReleaseAll()
{
	for (int nPriority = PRIORITY_NONE; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene *UninitObj = m_pTop[nPriority];				// 操作するオブジェクト

		while (UninitObj != NULL)
		{
			if (UninitObj->GetPriority() != PRIORITY_FADE)
			{
				UninitObj->Uninit();
			}

			UninitObj = UninitObj->m_pNext;		// 操作するオブジェクトをm_pNextにする
		}
	}
}

//=============================================================================
// オブジェクトをひとつ消す
//=============================================================================
void CScene::Release(int nPriority)
{
	//=============================================================================
	// m_pTop、m_pBot関連の処理
	//=============================================================================
	if (this == m_pTop[nPriority] &&
		this == m_pBot[nPriority])
	{
		m_pTop[nPriority] = NULL;
		m_pBot[nPriority] = NULL;
		m_pNext = NULL;
		m_pPrev = NULL;
	}

	else if (this == m_pTop[nPriority])
	{
		m_pTop[nPriority] = m_pNext;
		m_pPrev = NULL;
		m_pNext->m_pPrev = NULL;		// m_pPrevを、thisのm_pPrevに設定
	}

	else if (this == m_pBot[nPriority])
	{
		m_pBot[nPriority] = m_pPrev;
		m_pNext = NULL;
		m_pPrev->m_pNext = NULL;		// m_pNextを、thisのm_pNextに設定
	}

	else
	{
		//=============================================================================
		// 次オブジェクトと前オブジェクトを結合
		//=============================================================================
		m_pNext->m_pPrev = m_pPrev;		// thisのm_pPrevを、m_pNextのm_pPrevに設定
		m_pPrev->m_pNext = m_pNext;		// thisのm_pNextを、m_pNextのm_pNextに設定
	}

	m_nNumAll--;				//ポリゴンの数を--
}

//=============================================================================
// 全てのオブジェクトを更新
//=============================================================================
void CScene::UpdateAll()
{
	for (int nPriority = PRIORITY_NONE; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene *UpdateObj = m_pTop[nPriority];				// 操作するオブジェクト

		while (UpdateObj)
		{
			if (UpdateObj->GetDeath())
			{
				CScene *UpdateObj2 = UpdateObj;		// UpdateObjを一時保管用変数に格納
				UpdateObj->Uninit();				// UpdateObjを削除
				UpdateObj = UpdateObj2->m_pNext;	// 操作するオブジェクトをm_pNextにする
			}

			else
			{
				UpdateObj->SetPosold(UpdateObj->GetPos());
				UpdateObj->Update();
				

				UpdateObj = UpdateObj->m_pNext;		// 操作するオブジェクトをm_pNextにする
			}
		}
	}
}

//=============================================================================
// 全てのオブジェクトを描画
//=============================================================================
void CScene::DrawAll()
{
	for (int nPriority = PRIORITY_NONE; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene *DrawObj = m_pTop[nPriority];				// 操作するオブジェクト

		while (DrawObj != NULL)
		{
			DrawObj->Draw();
			DrawObj = DrawObj->m_pNext;			// 操作するオブジェクトをm_pNextにする
		}
	}
}

//=============================================================================
// オブジェクトを初期位置に戻す
//=============================================================================
void CScene::ReturnTostartPos(CScene *scene)
{
	CScene *ReturnObj = scene;				// 操作するオブジェクト

	if(ReturnObj != NULL)
	{
		if (ReturnObj->GetPriority() != PRIORITY_FADE)
		{
			ReturnObj->SetPos(ReturnObj->GetstartPos());
			ReturnObj->SetPosold(ReturnObj->GetstartPos());
			ReturnObj->SetMove(ReturnObj->GetstartMove());
		}
	}
}

//=============================================================================
// オブジェクトを初期位置に戻す
//=============================================================================
void CScene::ReturnTostartPosAll()
{
	for (int nPriority = PRIORITY_NONE; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene *ReturnObj = m_pTop[nPriority];				// 操作するオブジェクト

		while (ReturnObj != NULL)
		{
			if (ReturnObj->GetPriority() != PRIORITY_FADE)
			{
				ReturnObj->SetPos(ReturnObj->GetstartPos());
				ReturnObj->SetPosold(ReturnObj->GetstartPos());
				ReturnObj->SetMove(ReturnObj->GetstartMove());

				for (int nCnt = 0; nCnt < DIRECTION_MAX; nCnt++)
				{
					ReturnObj->SetColision(NULL, nCnt);
				}
			}

			ReturnObj = ReturnObj->m_pNext;		// 操作するオブジェクトをm_pNextにする
		}
	}
}

//=============================================================================
// 数値の符号を取得する
//=============================================================================
int CScene::Sign(float num)
{
	// numが1以上なら1を返す
	if (num > 0)
	{
		return 1;
	}

	// numが-1以下なら1を返す
	if (num < 0)
	{
		return -1;
	}

	// numが0なら0を返す
	return 0;
}

void CScene::RandomShake(D3DXVECTOR3 shakerand)
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_real_distribution<> randX(-shakerand.x, shakerand.x);
	std::uniform_real_distribution<> randY(-shakerand.y, shakerand.y);

	D3DXVECTOR3 rand;
	rand.x = (float)randX(mt);
	rand.y = (float)randY(mt);
	rand.z = 0.0f;

	for (int nPriority = PRIORITY_BGOBJECT; nPriority < PRIORITY_OBJMAX; nPriority++)
	{
		CScene *SetPosObj = m_pTop[nPriority];		// 操作するオブジェクト

		while (SetPosObj != NULL)
		{
			SetPosObj->SetPos(SetPosObj->GetPos() + rand);
			SetPosObj = SetPosObj->m_pNext;			// 操作するオブジェクトをm_pNextにする
		}
	}
}