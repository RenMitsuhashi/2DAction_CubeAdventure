//=============================================================================
//
// ステージ生成 [stageload.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "stageload.h"

#include "player.h"
#include "normalblock.h"
#include "targetblock.h"
#include "tentativeobj.h"
#include "goal.h"

#include "light.h"
#include "planet.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "gravityreverse.h"
#include "spiny.h"
#include "pause.h"

CPlayer				*CStageLoad::m_pPlayer		= NULL;
CNormalBlock		*CStageLoad::m_pNormalBlock = NULL;
CTargetBlock		*CStageLoad::m_pTargetBlock = NULL;
CGoal				*CStageLoad::m_pGoal		= NULL;
CGravityReverse		*CStageLoad::m_pReverse		= NULL;
CSpiny				*CStageLoad::m_pSpiny		= NULL;
CPause				*CStageLoad::m_pPause		= NULL;

const D3DXVECTOR3	CStageLoad::m_Grid			= D3DXVECTOR3(30.0f, 30.0f, 0.0f);

int					CStageLoad::objQuantity[]	= {};

D3DXVECTOR3			CStageLoad::m_MaxStage		= {};

//=============================================================================
// コンストラクタ
//=============================================================================
CStageLoad::CStageLoad()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CStageLoad::~CStageLoad()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStageLoad::Init(void)
{
	return S_OK;
}

//=============================================================================
// ステージファイルのロード
//=============================================================================
HRESULT CStageLoad::LoadFile(const char *FileName)
{
	if (m_pPause)
	{
		m_pPause->SetDeath(true);
		m_pPause = NULL;
	}

	m_pPause = CPause::Create(CTexture::GetTexture(CTexture::Tex_Pause_Cursor));

	m_MaxStage.x = 0.0f;
	m_MaxStage.y = 0.0f;
	m_MaxStage.z = 0.0f;

	std::vector<string> GridData = {};

	// 「オブジェクトの残量」変数の初期化
	objQuantity[OBJ_NULL] = 0;
	objQuantity[OBJ_NormalBlock] = 10000;
	objQuantity[OBJ_TargetBlock] = objQuantity[OBJ_NormalBlock];
	objQuantity[OBJ_Player] = 1;
	objQuantity[OBJ_Reverse] = 100;
	objQuantity[OBJ_Goal] = 1;
	objQuantity[OBJ_Spiny] = 10000;

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
	// ファイル読み込み
	//=============================================================================
	// ファイルの中身を一行ずつ読み取る
	while (getline(File, strY))
	{
		float movex = 0.0f, movey = 0.0f;
		int targetx = 0, targety = 0, stoptime = 0;
		int ptn = 0;

		D3DCOLORVALUE col;
		col.r = 255.0f;
		col.g = 255.0f;
		col.b = 255.0f;
		col.a = 255.0f;

		GridData.reserve(y + 1);

		string strX = "";
		istringstream FileY(strY);

		// 区切り文字がなくなるまで文字を区切っていく
		while (getline(FileY, strX, ','))
		{
			if (strX == "")
			{
				strX = "0";
			}

			// 区切られた文字が入る
			GridData.push_back(strX);

			if (strX.find("m") == 0)
			{
				// strXにmxの文字があったら
				if (strX.find("x") == 1)
				{
					// 次のブロックのmovexを変更
					strX.erase(0, 2);
					movex = stof(strX);
				}

				// strXにmyの文字があったら
				else if (strX.find("y") == 1)
				{
					// 次のブロックのmoveyを変更
					strX.erase(0, 2);
					movey = stof(strX);
				}
			}

			else if (strX.find("t") == 0)
			{
				// strXにtxの文字があったら
				if (strX.find("x") == 1)
				{
					// 次のブロックのtargetxを変更
					strX.erase(0, 2);
					targetx = stoi(strX);
				}

				// strXにtyの文字があったら
				else if (strX.find("y") == 1)
				{
					// 次のブロックのtargetyを変更
					strX.erase(0, 2);
					targety = stoi(strX);
				}

				// strXにtsの文字があったら
				else if (strX.find("s") == 1)
				{
					// 次のブロックのmoveを変更
					strX.erase(0, 2);
					stoptime = stoi(strX);
				}
			}

			else if (strX.find("c") == 0)
			{
				// strXにcrの文字があったら
				if (strX.find("r") == 1)
				{
					// 次のブロックのtargetxを変更
					strX.erase(0, 2);
					col.r = stof(strX);
				}

				// strXにcgの文字があったら
				else if (strX.find("g") == 1)
				{
					// 次のブロックのtargetyを変更
					strX.erase(0, 2);
					col.g = stof(strX);
				}

				// strXにcbの文字があったら
				else if (strX.find("b") == 1)
				{
					// 次のブロックのmoveを変更
					strX.erase(0, 2);
					col.b = stof(strX);
				}

				// strXにcaの文字があったら
				else if (strX.find("a") == 1)
				{
					// 次のブロックのmoveを変更
					strX.erase(0, 2);
					col.a = stof(strX);
				}
			}

			else if (strX.find("p") == 0)
			{
				// 次のブロックのmovexを変更
				strX.erase(0, 1);
				ptn = stof(strX);
			}

			else
			{
				StageCreate(stoi(strX), D3DXVECTOR3(((float)x * m_Grid.x), ((float)y * m_Grid.y), 0.0f), D3DXVECTOR3(movex, movey, 0.0f), D3DXVECTOR3((float)targetx, (float)targety, 0.0f), stoptime, ptn, col);

				x++;
				movex = 0.0f;
				movey = 0.0f;
				targetx = 0;
				targety = 0;
				ptn = 0;

				col.r = 255.0f;
				col.g = 255.0f;
				col.b = 255.0f;
				col.a = 255.0f;
			}
		}

		x = 0;
		y++;  // 次の配列に移る
	}

	return S_OK;
}

//=============================================================================
// ステージファイルのセーブ
//=============================================================================
HRESULT CStageLoad::SaveFile()
{
	// ファイルに書き込む
	ofstream File("data\\stage\\stage.csv");

	if (!File)
	{
		return E_FAIL;
	}

	for (int numy = 0; numy <= (int)m_MaxStage.y; numy += (int)GetGrid().y)
	{
		for (int numx = 0; numx <= (int)m_MaxStage.x; numx += (int)GetGrid().x)
		{
			CTentativeObj *SaverObj = CTentativeObj::Create(D3DXVECTOR3((float)numx, (float)numy, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CScene *CoverObj = SaverObj->CoverBlock(SaverObj);

			if (CoverObj != NULL)
			{
				// 移動量決め
				float movex = 0.0f, movey = 0.0f;
				movex = CoverObj->GetMove().x;
				movey = CoverObj->GetMove().y;

				if (movex != 0.0f)
				{
					File << "mx" << movex << ",";
				}

				if (movey != 0.0f)
				{
					File << "my" << movey << ",";
				}

				// ターゲット、移動時間決め
				int targetx = 0, targety = 0, stoptime = 0;
				targetx = (int)CoverObj->GetTargetPos().x;
				targety = (int)CoverObj->GetTargetPos().y;
				stoptime = CoverObj->GetStopTime();

				if (targetx != 0.0f)
				{
					File << "tx" << targetx / m_Grid.x << ",";
				}

				if (targety != 0.0f)
				{
					File << "ty" << targety / m_Grid.y << ",";
				}

				if (stoptime != 0.0f)
				{
					File << "ts" << stoptime << ",";
				}

				// 色決め
				D3DCOLORVALUE col;
				col = CoverObj->GetCol();

				if (col.r != 255.0f)
				{
					File << "cr" << col.r << ",";
				}

				if (col.g != 255.0f)
				{
					File << "cg" << col.g << ",";
				}

				if (col.b != 255.0f)
				{
					File << "cb" << col.b << ",";
				}

				if (col.a != 255.0f)
				{
					File << "ca" << col.a << ",";
				}

				// テクスチャ分割数決め
				if (CoverObj->GetPtn() != 0)
				{
					File << "p" << CoverObj->GetPtn() << ",";
				}

				// タイプ決め
				int type = 0;
				type = CoverObj->GetobjType();

				File << type << ",";
			}

			else
			{
				File << ",";
			}

			SaverObj->Uninit();
		}

		File << endl;
	}

	return S_OK;
}

void CStageLoad::StageCreate(int type, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 targetpos, int stoptime, int ptn, D3DCOLORVALUE col)
{
	if (objQuantity[type] > 0)
	{
		switch (type)
		{
		case OBJ_NormalBlock:
			move.x *= CScene::Sign(targetpos.x);
			move.y *= CScene::Sign(targetpos.y);

			m_pNormalBlock = CNormalBlock::Create(D3DXVECTOR3(pos.x + m_Grid.x / 2.0f, pos.y + m_Grid.y / 2.0f, 0.0f), D3DXVECTOR3(move.x, move.y, 0.0f), D3DXVECTOR3(m_Grid.x, m_Grid.y, 0.0f), D3DXVECTOR3(targetpos.x * GetGrid().x, targetpos.y * GetGrid().y, 0.0f), stoptime, CTexture::GetTexture(CTexture::Tex_NormalBlock));
			m_pNormalBlock->SetobjType(type);
			m_pNormalBlock->SetColor(col);

			if (m_pNormalBlock->GetTargetPos() != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_pTargetBlock = CTargetBlock::Create(m_pNormalBlock->GetPos() + m_pNormalBlock->GetTargetPos(), m_pNormalBlock->GetMove(), m_pNormalBlock->GetSize(), D3DXVECTOR3(m_pNormalBlock->GetTargetPos().x * -1.0f, m_pNormalBlock->GetTargetPos().y * -1.0f, 0.0f), 0, CTexture::GetTexture(CTexture::Tex_NormalBlock));
				m_pTargetBlock->SetobjType(OBJ_TargetBlock);

				minusQuantity(OBJ_TargetBlock);
			}

			break;

		case OBJ_Player:
			m_pPlayer = CPlayer::Create(D3DXVECTOR3(pos.x + m_Grid.x / 2, pos.y + m_Grid.y / 2, 0.0f), D3DXVECTOR3(move.x, move.y, 0.0f), D3DXVECTOR3(m_Grid.x - (m_Grid.x / 8.0f), m_Grid.y - (m_Grid.y / 8.0f), 0.0f), CTexture::GetTexture(CTexture::Tex_Player));
			m_pPlayer->SetobjType(type);

			break;

		case OBJ_Reverse:
			m_pReverse = CGravityReverse::Create(D3DXVECTOR3(pos.x + m_Grid.x / 2, pos.y + m_Grid.y / 2, 0.0f), D3DXVECTOR3(move.x, move.y, 0.0f), D3DXVECTOR3(m_Grid.x, m_Grid.y, 0.0f), CTexture::GetTexture(CTexture::Tex_Reverse));
			m_pReverse->SetobjType(type);

			break;

		case OBJ_Goal:
			m_pGoal = CGoal::Create(D3DXVECTOR3(pos.x + m_Grid.x / 2, pos.y + m_Grid.y / 2, 0.0f), D3DXVECTOR3(move.x, move.y, 0.0f), D3DXVECTOR3(m_Grid.x, m_Grid.y, 0.0f), CTexture::GetTexture(CTexture::Tex_Goal));
			m_pGoal->SetobjType(type);

			break;

		case OBJ_Spiny:
			m_pSpiny = CSpiny::Create(D3DXVECTOR3(pos.x + m_Grid.x / 2, pos.y + m_Grid.y / 2, 0.0f), D3DXVECTOR3(move.x, move.y, 0.0f), D3DXVECTOR3(m_Grid.x, m_Grid.y, 0.0f), ptn, CTexture::GetTexture(CTexture::Tex_Spiny));
			m_pSpiny->SetobjType(type);

			break;
		}

		minusQuantity(type);
	}
	
	if (type != 0)
	{
		if (m_MaxStage.x < pos.x)
		{
			m_MaxStage.x = pos.x;
		}

		if (m_MaxStage.y < pos.y)
		{
			m_MaxStage.y = pos.y;
		}
	}
}