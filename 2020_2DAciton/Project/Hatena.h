#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"Item.h"

class CHatena
{
private:
	CTexture*				m_pTexture;		//テクスチャ
	float					m_PosX;
	float					m_PosY;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bShow;
	CRectangle				m_SrcRect;
	bool					m_bItem;
public:
	CHatena();
	~CHatena();
	void Initialize(float px, float py);
	void Update(void);
	void CollisionPlayer(CRectangle prec, CItem& pItem);
	void Render(float wx, float wy);
	void Release(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	void SetShow(bool bs) { m_bShow = bs; }
	CRectangle GetRect() { return CRectangle(m_PosX, m_PosY, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight()); }
};

