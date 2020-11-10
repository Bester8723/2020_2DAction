/*************************************************************************//*!

					@file	SceneBase.h
					@brief	シーン基礎。

															@author	池上　綾香
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"MOF.h"


class CSceneBase {
protected:
	bool				m_bEnd;						//シーン終了フラグ
	int					m_NextScene;				//次のシーン
	CTexture			m_BackTexture;				//背景テクスチャ
	
public:
	//コンストラクタ
	CSceneBase() :
		m_bEnd(false),
		m_NextScene(0), 
		m_BackTexture() {
	}
	virtual ~CSceneBase() {};
	virtual bool Load(void) = 0;
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
	virtual void RenderDebug(void) = 0;
	virtual void Release(void) = 0;
	//次のシーンを取得
	int GetNextScene(void) { return m_NextScene; }
	//シーンは終了したか
	bool IsEnd(void) { return m_bEnd; }
};