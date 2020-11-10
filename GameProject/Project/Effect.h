/*************************************************************************//*!

					@file	Effect.h
					@brief	エフェクトの中身。

															@author	池上　綾香
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"Mof.h"
#include	"EffectManager.h"


//エフェクト種類列挙
enum tag_EFFECTTYPE {
	EFC_DAMAGE,						//ダメージ
	EFC_EXPLOSION01,				//敵爆破
	EFC_EXPLOSION02,				//プレイヤー爆破

	EFC_TYPECOUNT,
};

class CEffect {
private:
	CTexture*					m_pTexture;
	CSpriteMotionController		m_Motion;
	float						m_PosX;
	float						m_PosY;
	bool						m_bShow;
	CRectangle					m_SrcRect;

public:
	CEffect();
	~CEffect();
	void Initialize(int type);
	void Start(float px,float py);
	void Update(void);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
};