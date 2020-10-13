#include "Hatena.h"

/**
 * コンストラクタ
 *
 */
CHatena::CHatena() : 
m_pTexture(NULL),
m_PosX(0.0f),
m_PosY(0.0f),
m_MoveX(0.0f),
m_MoveY(0.0f),
m_bShow(false),
m_SrcRect() ,
m_bItem(false) {
}

/**
 * デストラクタ
 *
 */
CHatena::~CHatena()
{
	//delete[] で解放されるようにReleaseをデストラクタで実行する
	Release();
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 *
 * 引数
 * [in]			px					X座標
 * [in]			py					Y座標
 */
void CHatena::Initialize(float px, float py)
{
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bShow = true;
	m_bItem = true;
	m_SrcRect = CRectangle(0, 0, 32, 32);
}

/**
 * 更新
 *
 */
void CHatena::Update(void)
{
	//非表示
	if (!m_bShow)
	{
		return;
	}
	
}

/**
 * プレイヤーとはてなブロックの当たり
 *
 * 引数
 * [in]				prec				プレイヤーの矩形
 * [in]				pItem				判定を行うアイテム
 */
void CHatena::CollisionPlayer(CRectangle prec, CItem& pItem)
{
	//はてなブロックの中にアイテムがないとき
	if (!m_bItem)
	{
		return;
	}
	//プレイヤー矩形の整理
	CRectangle trec = prec;
	trec.Bottom = trec.Top + 1;
	trec.Top -= 2;
	trec.Left -= 2;
	trec.Right -= 2;
	//はてなブロックとプレイヤーの矩形が当たっていたら
	if (GetRect().CollisionRect(trec))
	{
		//はてなブロックと当たっているアイテムを探す
		if (GetRect().CollisionRect(pItem.GetRect()))
		{
			pItem.Drop();
			m_bItem = false;
			m_SrcRect = CRectangle(32, 0, 64, 32);
		}
	}
}

/**
 * 描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CHatena::Render(float wx, float wy)
{
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, m_SrcRect);
}

/**
 * 解放
 *
 */
void CHatena::Release(void)
{
}
