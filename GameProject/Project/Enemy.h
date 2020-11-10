#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"EffectManager.h"


//ìñÇΩÇËîªíËå∏êäïù
#define		ENEMY_RECTDECREASE		10

class CEnemy {
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	float					m_PosX;
	float					m_PosY;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bShow;
	bool					m_bReverse;
	CRectangle				m_SrcRect;
	int						m_HP;
	int						m_DamageWait;
	CEffectManager*			m_pEffectManager;
	
	//ÉÇÅ[ÉVÉáÉìéÌóﬁíËã`
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};
public:
	CEnemy();
	~CEnemy();
	void Initialize(float px,float py,int type);
	void Update(float wx, float wy);
	void CollisionStage(float ox,float oy);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
	CRectangle GetRect(){
		return CRectangle(m_PosX + ENEMY_RECTDECREASE,m_PosY + ENEMY_RECTDECREASE,m_PosX + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
	}
	void Damage(int dmg, bool bRev);
	int GetDamageWait(void) { return m_DamageWait; }
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }
	void SetMoveX() {
		if (m_MoveX < 0)
		{
			m_bReverse = false;
			m_MoveX = 3.0f;
		}
		else if (m_MoveY > 0)
		{
			m_bReverse = true;
			m_MoveX = -3.0f;
		}
	}
	CRectangle GetCollisionRect() {
		CRectangle vrec;
		if (m_bReverse)
			vrec = CRectangle(m_PosX - 30, m_PosY, m_PosX, m_PosY + m_SrcRect.GetHeight() + 30);
		else
			vrec = CRectangle(m_PosX + m_SrcRect.GetWidth(), m_PosY, m_PosX + m_SrcRect.GetWidth() + 30, m_PosY + m_SrcRect.GetHeight() + 30);
		return vrec;
	}
};