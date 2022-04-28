//=============================================================================
//
// ステージ [stage.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "stage.h"

#include "player.h"
#include "normalblock.h"

#include "light.h"
#include "planet.h"

CPlayer				*CStage::m_pPlayer = NULL;
CNormalBlock		*CStage::m_pNormalBlock = NULL;

const D3DXVECTOR3	CStage::m_Grid = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
bool				CStage::m_isLoad[] = {};

int					CStage::m_nMaxGridX = 0;
int					CStage::m_nMaxGridY = 0;

std::vector<vector<string>> CStage::m_GridData = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CStage::CStage()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CStage::~CStage()
{

}

//=============================================================================
// ステージファイルのロード
//=============================================================================
HRESULT CStage::LoadFile(const char *FileName)
{
	// ファイルを読み込む
	ifstream File(FileName);

	if (!File)
	{
		return E_FAIL;
	}

	string strY = "";
	int x = 0;
	int y = 0;

	//=============================================================================
	// ステージの大きさ.x設定
	//=============================================================================
	while (getline(File, strY, ','))
	{
		x++;
	}

	m_nMaxGridX = x;
	x = 0;

	m_GridData.resize(m_nMaxGridX, vector<string>(m_nMaxGridY));

	//=============================================================================
	// ファイル読み込み
	//=============================================================================
	// ファイルの中身を一行ずつ読み取る
	while (getline(File, strY))
	{
		// ステージの大きさ.y更新
		m_nMaxGridY++;
		m_GridData.resize(m_nMaxGridX, vector<string>(m_nMaxGridY));

		string strX = "";
		istringstream FileY(strY);

		// 区切り文字がなくなるまで文字を区切っていく
		while (getline(FileY, strX, ','))
		{
			// 区切られた文字が入る
			m_GridData[x][y] = strX;
			x++;
		}

		x = 0;
		y++;  // 次の配列に移る
	}

	return S_OK;
}

void CStage::StageCreate(int x, int y)
{
	int nStageData = atoi(m_GridData[x][y].c_str());
	D3DXVECTOR3 size = D3DXVECTOR3((m_Grid.x / 2.0f), (m_Grid.y / 2.0f), 0.0f);

	switch (nStageData)
	{
	case OBJ_NormalBlock:
		CNormalBlock::Load();
		m_pNormalBlock = CNormalBlock::Create(D3DXVECTOR3(x + size.x, y + size.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, size.y / 2.0f, 0.0f));

		break;

	case OBJ_Player:
		CPlayer::Load();
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(x + size.x, y + size.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, size.y / 2.0f, 0.0f));

		break;
	}

	m_isLoad[nStageData] = true;
}

void CStage::UnloadTexture()
{
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		if (m_isLoad[nCnt])
		{
			switch (nCnt)
			{
			case OBJ_NormalBlock:
				CNormalBlock::Unload();

				break;

			case OBJ_Player:
				CPlayer::Unload();

				break;
			}

			m_isLoad[nCnt] = true;
		}
	}
}