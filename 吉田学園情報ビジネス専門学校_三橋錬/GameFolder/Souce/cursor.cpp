//=============================================================================
//
// カーソル [cursor.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "cursor.h"
#include "manager.h"
#include "renderer.h"

#include "input.h"
#include "keyboard.h"
#include "gamepad.h"
#include "mouse.h"
#include "stagebuild.h"
#include "player.h"

#include "sound.h"
#include "data.h"
#include "tentativeobj.h"
#include "texture.h"
#include "fade.h"
#include "uibg.h"
#include "pause.h"

#include <assert.h>

CTargetCursor *CCursor::m_pTargetCursor = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CCursor::CCursor(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CCursor::~CCursor()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CCursor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CScene2D::Init(tex);

	SetPos(pos + GetGrid() / 2);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	m_nType = OBJ_NormalBlock;
	m_move = 0.0f;
	TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_stoptime = 0;

	m_nColisionType = OBJ_NULL;
	m_Colisionmove = 0.0f;
	m_Colisionstoptime = 0;

	m_pTargetCursor = CTargetCursor::Create(move, size, tex);

	m_col.r = 255.0f;
	m_col.g = 255.0f;
	m_col.b = 255.0f;
	m_col.a = 255.0f;

	m_Colisioncol.r = 255.0f;
	m_Colisioncol.g = 255.0f;
	m_Colisioncol.b = 255.0f;
	m_Colisioncol.a = 255.0f;

	CData::ZeroMoveQuantity();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CCursor::Uninit()
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CCursor::Update()
{
	m_nColisionType = OBJ_NULL;		// 現在当たっているオブジェクトの種類
	m_Colisionmove = 0.0f;			// 現在当たっているオブジェクトの移動量
	m_Colisionstoptime = 0;			// 現在当たっているオブジェクトの移動までの時間

	int tex = CTexture::Tex_NormalBlock - 1;

	D3DCOLORVALUE col;
	col.r = 255.0f;
	col.g = 255.0f;
	col.b = 255.0f;
	col.a = 255.0f;

	if (!CData::GetNowGame() &&
		CData::GetPause())
	{
		// カーソルのposはマウスの座標を代入させる
		D3DXVECTOR3 mouse = CManager::GetRenderer()->GetMousePos();
		D3DXVECTOR3 pos = D3DXVECTOR3(floorf(mouse.x / GetSize().x) * GetSize().x, floorf(mouse.y / GetSize().y) * GetSize().y, 0.0f);

		SetPositionCenter(pos + GetGrid() / 2, GetSize());

		SetPos(pos + GetGrid() / 2);

		// 画面スクロールに対応させる
		SetPosX(pos.x + CData::GetMoveQuantity() + GetGrid().x / 2);

		//=============================================================================
		// 配置するオブジェクトを切り替える
		//=============================================================================
		// 下キー
		if (CManager::GetKeyboard()->GetTrigger(DIK_DOWN))
		{
			// 配置するオブジェクトの種類を切り替え
			m_nType++;

			// 選べる種類の限界を突破したら
			if (m_nType == OBJ_TargetBlock)
			{
				// 一番最初のオブジェクトへm_nTypeをずらす
				m_nType = OBJ_NULL + 1;
			}

			// 選ばれたオブジェクトのテクスチャに変更させる
			BindTexture(CTexture::GetTexture(m_nType + tex));
		}

		// 上キー
		if (CManager::GetKeyboard()->GetTrigger(DIK_UP))
		{
			// 配置するオブジェクトの種類を切り替え
			m_nType--;

			// 選べる種類の限界を突破したら
			if (m_nType == OBJ_NULL)
			{
				// 一番最後のオブジェクトへm_nTypeをずらす
				m_nType = OBJ_TargetBlock - 1;
			}

			// 選ばれたオブジェクトのテクスチャに変更させる
			BindTexture(CTexture::GetTexture(m_nType + tex));
		}

		if (m_nType == OBJ_Goal)
		{
			// ゴール用はテクスチャ座標をずらす
			SetTexture(0, D3DXVECTOR2(4.0f, 1.0f));
		}

		else if (m_nType == OBJ_Spiny)
		{
			// 棘は向きによってテクスチャ座標をずらす
			SetTexture(m_nSpinyDirection, D3DXVECTOR2(2.0f, 1.0f));
		}

		// 何かがおかしい時はここを通る
		else
		{
			SetTexture(0, D3DXVECTOR2(1.0f, 1.0f));
		}

		//=============================================================================
		// 画面スクロール
		//=============================================================================
		// 左キー
		if (CManager::GetKeyboard()->GetPress(DIK_LEFT))
		{
			CData::MoveQuantity(-GetGrid().x);
		}

		// 右キー
		if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))
		{
			CData::MoveQuantity(GetGrid().x);
		}

		// (〇〇をプラス)の増加量
		int mul = 1;

		if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
		{
			mul *= 10;
		}

		if (CManager::GetKeyboard()->GetPress(DIK_LCONTROL))
		{
			mul *= -1;
		}

		//=============================================================================
		// m_moveの変更
		//=============================================================================
		// Rキー
		if (CManager::GetKeyboard()->GetTrigger(DIK_R))
		{
			m_move += float(mul) / 10.0f;
		}

		// m_moveの誤差をつぶす
		m_move = roundf(m_move * 10.0f) / 10.0f;

		// 最大値、最小値を超過しないよう直す
		if (m_move > m_moveMax)
		{
			m_move = m_moveMax;
		}

		if (m_move < 0)
		{
			m_move = 0;
		}

		//=============================================================================
		// m_stoptimeの変更
		//=============================================================================
		// Fキー
		if (CManager::GetKeyboard()->GetTrigger(DIK_F))
		{
			m_stoptime += mul;
		}

		// 最大値、最小値を超過しないよう直す
		if (m_stoptime > m_stopMax)
		{
			m_stoptime = m_stopMax;
		}

		if (m_stoptime < 0)
		{
			m_stoptime = 0;
		}

		//=============================================================================
		// m_colの変更
		//=============================================================================
		if (CManager::GetKeyboard()->GetTrigger(DIK_Z))
		{
			m_col.r += mul;

			// 最大値、最小値を超過しないよう直す
			if (m_col.r > 255)
			{
				m_col.r = 255;
			}

			if (m_col.r < 0)
			{
				m_col.r = 0;
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_X))
		{
			m_col.g += mul;

			// 最大値、最小値を超過しないよう直す
			if (m_col.g > 255)
			{
				m_col.g = 255;
			}

			if (m_col.g < 0)
			{
				m_col.g = 0;
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_C))
		{
			m_col.b += mul;

			// 最大値、最小値を超過しないよう直す
			if (m_col.b > 255)
			{
				m_col.b = 255;
			}

			if (m_col.b < 0)
			{
				m_col.b = 0;
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_V))
		{
			m_col.a += mul;

			// 最大値、最小値を超過しないよう直す
			if (m_col.a > 255)
			{
				m_col.a = 255;
			}

			if (m_col.a < 0)
			{
				m_col.a = 0;
			}
		}

		//=============================================================================
		// オブジェクトの削除
		//=============================================================================
		int TargetCount = 0;
		bool Cover = false;

		if (TargetPos.x != 0)
		{
			TargetCount = (int)TargetPos.x;
		}

		else if (TargetPos.y != 0)
		{
			TargetCount = (int)TargetPos.y;
		}

		// 当たり判定取得用の仮オブジェクト作成
		CTentativeObj *ColisionObj = CTentativeObj::Create(GetPos() - GetGrid() / 2, D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetSize() / 2.0f);

		for(int num = 0; num <= abs(TargetCount); num++)
		{
			CScene *scene = CoverMoveBlock(ColisionObj);
			// 何かオブジェクトとかぶさっていたら
			if (scene != NULL)
			{
				if (scene->GetMove().x != 0)
				{
					m_Colisionmove = fabs(scene->GetMove().x);
				}

				else if (scene->GetMove().y != 0)
				{
					m_Colisionmove = fabs(scene->GetMove().y);
				}

				m_nColisionType = scene->GetobjType();
				m_Colisionstoptime = scene->GetStopTime();
				m_Colisioncol = scene->GetCol();

				Cover = true;
				break;
			}

			if (TargetPos.x != 0)
			{
				ColisionObj->SetPosX(ColisionObj->GetPos().x + float(Sign(TargetPos.x)) * GetGrid().x);
			}

			else if (TargetPos.y != 0)
			{
				ColisionObj->SetPosY(ColisionObj->GetPos().y + float(Sign(TargetPos.y)) * GetGrid().y);
			}
		}

		ColisionObj->Uninit();

		if (Cover)
		{
			col.g = 0.0f;
			col.b = 0.0f;
			col.a = 128.0f;

			// 右クリック
			if (CManager::GetMouse()->GetPress(CMouse::DIM_R))
			{
				// オブジェクトを削除、残量を増やす
				CoverMoveBlock(ColisionObj)->SetDeath(true);
				plusQuantity(m_nColisionType);
			}
		}

		//=============================================================================
		// オブジェクトの配置
		//=============================================================================
		else
		{
			col.a = 128.0f;

			// 枠外なら配置はできない
			if (GetPos().x < 0.0f)
			{
				col.g = 0.0f;
				col.b = 0.0f;
			}

			else
			{
				// 左クリック
				if (CManager::GetMouse()->GetPress(CMouse::DIM_L))
				{
					if (m_nType == OBJ_Player)
					{
						if (GetQuantity(OBJ_Player) == 0)
						{
							plusQuantity(OBJ_Player);
						}

						PlayerReCreate();
					}

					D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					if (TargetPos.x != 0)
					{
						move.x = m_move;
					}

					else if (TargetPos.y != 0)
					{
						move.y = m_move;
					}

					// オブジェクトを配置する
					StageCreate(m_nType, D3DXVECTOR3((pos.x + CData::GetMoveQuantity()), pos.y, 0.0f), move, D3DXVECTOR3(TargetPos.x, TargetPos.y, 0.0f), m_stoptime, m_nSpinyDirection, m_col);
				}
			}
		}

		if (m_nType == OBJ_Spiny)
		{
			if (CManager::GetKeyboard()->GetTrigger(DIK_W))
			{
				m_nSpinyDirection--;

				if (m_nSpinyDirection < 0)
				{
					m_nSpinyDirection = 0;
				}
			}

			if (CManager::GetKeyboard()->GetTrigger(DIK_S))
			{
				m_nSpinyDirection++;

				if (m_nSpinyDirection > 1)
				{
					m_nSpinyDirection = 1;
				}
			}
		}

		if (m_nType == OBJ_NormalBlock)
		{
			if (TargetPos.x == 0.0f)
			{
				if (CManager::GetKeyboard()->GetTrigger(DIK_W))
				{
					TargetPos.y -= 1.0f;
				}

				if (CManager::GetKeyboard()->GetTrigger(DIK_S))
				{
					TargetPos.y += 1.0f;
				}
			}

			if (TargetPos.y == 0.0f)
			{
				if (CManager::GetKeyboard()->GetTrigger(DIK_A))
				{
					TargetPos.x -= 1.0f;
				}

				if (CManager::GetKeyboard()->GetTrigger(DIK_D))
				{
					TargetPos.x += 1.0f;
				}
			}
		}

		if (CManager::GetMouse()->GetTrigger(CMouse::DIM_W))
		{
			if (CoverMoveBlock(ColisionObj))
			{
				if (CoverMoveBlock(ColisionObj)->GetPriority() == CScene::PRIORITY_BLOCK)
				{
					float x = CoverMoveBlock(ColisionObj)->GetTargetPos().x / GetGrid().x;
					float y = CoverMoveBlock(ColisionObj)->GetTargetPos().y / GetGrid().y;

					TargetPos = D3DXVECTOR3(x, y, 0.0f);
				}

				m_move = m_Colisionmove;
				m_stoptime = m_Colisionstoptime;

				m_col = CoverMoveBlock(ColisionObj)->GetCol();
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
		{
			TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move = 0.0f;
			m_stoptime = 0;

			m_col.r = 255.0f;
			m_col.g = 255.0f;
			m_col.b = 255.0f;
			m_col.a = 255.0f;
		}

		// セーブ中
		if (CPause::GetNowSave())
		{
			// オブジェクトを削除、残量を増やす
			SaveFile();
			m_nNowSave = 256;
		}
	}

	//=============================================================================
	// 全オブジェクトを初期位置に戻し、設置モードとプレイモードを入れ替える
	//=============================================================================

	if (CData::GetPause() && CStageLoad::GetPlayer())
	{
		if (!CStageLoad::GetPlayer()->GetDeath())
		{
			// エンターキー
			if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
			{
				CData::ChangeNowGame();
				CData::ZeroMoveQuantity();
				ReturnTostartPosAll();
			}
		}
	}

	SetColor(col);
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CCursor::Draw()
{
	if (!CData::GetNowGame())
	{
		CScene2D::Draw();
		DrawObjInfo();
	}
}

CCursor *CCursor::Create(D3DXVECTOR3 speed, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CCursor* pCursor = new CCursor;

	if (pCursor != NULL)
	{
		pCursor->Init(CManager::GetRenderer()->GetMousePos(), speed, size, tex);
	}
	return pCursor;
}

//=============================================================================
// オブジェクトの詳細を表示
//=============================================================================
void CCursor::DrawObjInfo()
{
	//=============================================================================
	// 配置予定のオブジェクト情報
	//=============================================================================
	{
		string strType;

		switch (m_nType)
		{
		case OBJ_NormalBlock:
			strType = "ブロック";

			break;

		case OBJ_Player:
			strType = "プレイヤー";

			break;

		case OBJ_Goal:
			strType = "ゴールオブジェクト";

			break;

		case OBJ_Reverse:
			strType = "重力反転オブジェクト";

			break;

		case OBJ_Spiny:
			strType = "棘オブジェクト";

			break;

		default:
			strType = "";

			break;
		}

		int recttop = SCREEN_HEIGHT / 16;
		RECT rect = { SCREEN_WIDTH - (SCREEN_WIDTH / 4), recttop, SCREEN_WIDTH, SCREEN_HEIGHT };
		RECT rectBg = rect;

		rectBg.left += 1;
		rectBg.top += 1;

		// テキスト描画
		string str = "\n**********************\n\n";

		// テキスト描画
		str += "現在のオブジェクト：" + strType + "\nオブジェクト残量：" + to_string(GetQuantity(m_nType)) + "\n";

		str += "\n**********************\n\n";
		
		if (m_nType == OBJ_NormalBlock)
		{
			// テキスト描画
			str += "\n******ブロック用******\n\n";

			str += "WASDキー　　: 目標地点を動かす\n\n";

			str += "Rキー　   　: 1fごとの移動距離をプラス(0.1f)\n";

			str += "Fキー　　   : 静止時間をプラス(1F)\n\n";

			str += "Zキー　　   : カラー値(赤)をプラス\n";
			str += "Xキー　　   : カラー値(緑)をプラス\n";
			str += "Cキー　　   : カラー値(青)をプラス\n";
			str += "Vキー　　   : カラー値(透明度)をプラス\n\n";

			str += "(LSHIFTキー同時押しで数値を*10)\n";
			str += "(LCTRLキー同時押しで数値をマイナスにする)\n\n";

			str += "マウスホイールクリック　: ブロックの詳細コピー\n";
			str += "スペースキー          　: ブロックの詳細リセット\n";

			str += "\n**********************\n\n";

			str += "ブロックの目標地点        : x=" + to_string(int(TargetPos.x)) + ", y=" + to_string(int(TargetPos.y)) + "\n";
			str += "ブロックの1fごとの移動距離: " + to_string(m_move) + "\n";
			str += "ブロックの静止時間        : " + to_string(m_stoptime) + "\n";

			str += "カラー値(赤)              : " + to_string((int)m_col.r) + "\n";
			str += "カラー値(緑)              : " + to_string((int)m_col.g) + "\n";
			str += "カラー値(青)              : " + to_string((int)m_col.b) + "\n";
			str += "カラー値(透明度)          : " + to_string((int)m_col.a) + "\n";

			str += "\n**********************\n\n";
		}

		string strBg = str;

		CManager::GetRenderer()->GetFont()->DrawText(NULL, strBg.c_str(), -1, &rectBg, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
		rect.top += CManager::GetRenderer()->GetFont()->DrawText(NULL, str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	//=============================================================================
	// 触れているオブジェクトの情報
	//=============================================================================
	{
		string strType;

		switch (m_nColisionType)
		{
		case OBJ_NormalBlock:
			strType = "ブロック";

			break;

		case OBJ_Player:
			strType = "プレイヤー";

			break;

		case OBJ_Goal:
			strType = "ゴールオブジェクト";

			break;

		case OBJ_Reverse:
			strType = "重力反転オブジェクト";

			break;

		case OBJ_Spiny:
			strType = "棘オブジェクト";

			break;

		default:
			strType = "";

			break;
		}

		RECT rect = { 0, SCREEN_HEIGHT / 6, 350, 700 };
		RECT rectBg = rect;

		rectBg.left += 1;
		rectBg.top += 1;

		// テキスト描画
		// テキスト描画
		string str = "*******操作方法*******\n\n";

		str += "左クリック　   : ブロック配置\n";
		str += "右クリック   　: ブロック消去\n";
		str += "矢印キー上下   : ブロックの種類を変更\n";
		str += "矢印キー左右   : 画面スクロール\n";
		str += "エンターキー   : ゲームのテスト\n";
		str += "エスケープキー : ポーズ\n";

		str += "\n**********************\n\n";

		str += "*****触れているオブジェクト*****\n\n";

		str += "オブジェクト          ：" + strType + "\n";

		if (m_nColisionType == OBJ_NormalBlock)
		{
			str += "1fあたりの移動量      ：" + to_string(m_Colisionmove) + "\n";
			str += "移動してからの静止時間：" + to_string(m_Colisionstoptime) + "\n";

			str += "カラー値(赤)          ：" + to_string(m_Colisioncol.r) + "\n";
			str += "カラー値(緑)          ：" + to_string(m_Colisioncol.g) + "\n";
			str += "カラー値(青)          ：" + to_string(m_Colisioncol.b) + "\n";
			str += "カラー値(透明度)      ：" + to_string(m_Colisioncol.a) + "\n";
		}

		str += "\n******************************\n\n";

		string strBg = str;

		CManager::GetRenderer()->GetFont()->DrawText(NULL, strBg.c_str(), -1, &rectBg, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
		rect.top += CManager::GetRenderer()->GetFont()->DrawText(NULL, str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	//=============================================================================
	// [セーブ中...]表示
	//=============================================================================
	if(m_nNowSave > 0)
	{
		m_nNowSave--;

		string str = "ステージをセーブしました...";

		RECT rect = { 0, SCREEN_HEIGHT / 12, SCREEN_WIDTH, SCREEN_HEIGHT };
		RECT rectBg = rect;

		rectBg.left += 1;
		rectBg.top += 1;

		string strBg = str;

		CManager::GetRenderer()->GetFont()->DrawText(NULL, strBg.c_str(), -1, &rectBg, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
		rect.top += CManager::GetRenderer()->GetFont()->DrawText(NULL, str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(m_nNowSave, 0xff, 0xff, 0xff));

		if (m_nNowSave < 0)
		{
			m_nNowSave = 0;
		}
	}
}