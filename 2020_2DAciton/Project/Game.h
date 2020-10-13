#pragma once

#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"EffectManager.h"
#include	"Hatena.h"

class CGame
{
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

