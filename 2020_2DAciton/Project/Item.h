#pragma once

#include	"Mof.h"
#include	"GameDefine.h"

//アイテム種類列挙
enum tag_ITEMTYPE {
	ITEM_RECOVER,					//回復
	ITEM_GOAL,						//ゴール

	ITEM_TYPECOUNT,
};

class CItem {
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	float					m_PosX;
	float					m_PosY;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bShow;
	CRectangle				m_SrcRect;
	bool					m_bCollision;

	//モーション種類定義
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_GOAL,

		MOTION_COUNT,
	};
public:
	CItem();
	~CItem();
	void Initialize(float px,float py,int type);
	void Update(void);
	void CollisionStage(float ox,float oy);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
	void SetShow(bool bs){ m_bShow = bs; }
	int GetType(void){ return m_Type; }
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,m_PosX + m_SrcRect.GetWidth(),m_PosY + m_SrcRect.GetHeight()); }
	void Drop();
	bool GetCollision(void) { return m_bCollision; }
	void SetCollision(bool bs) { m_bCollision = bs; }
};