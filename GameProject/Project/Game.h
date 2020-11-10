/*************************************************************************/ /*!

					@file	Game.h
					@brief	ゲーム画面。

															@author	池上　綾香
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"SceneBase.h"
#include	"GameDefine.h"

#include	"EffectManager.h"
#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"Hatena.h"

class CGame : public CSceneBase {
private:
	//プレイヤー
	CPlayer			m_Player;
	//ステージ
	CStage			m_Stage;
	//敵
	CEnemy*			m_EnemyArray;
	//エフェクト
	CEffectManager	m_EffectManager;
	//アイテム
	CItem*			m_ItemArray;
	//はてなブロック
	CHatena*		m_HatenaArray;
	//ＨＰ
	CTexture		m_Texture;

public:
	CGame();
	~CGame();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

