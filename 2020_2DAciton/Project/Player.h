#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"Enemy.h"
#include	"EffectManager.h"
#include	"Item.h"

//移動速度
#define		PLAYER_SPEED			0.4f

//移動最大速度
#define		PLAYER_MAXSPEED			8.0f

//ジャンプ速度
#define		PLAYER_JUMP				-13.0f

//当たり判定減衰幅
#define		PLAYER_RECTDECREASE		12

class CPlayer
{
private:
	CTexture					m_Texture;			//テクスチャ
	CSpriteMotionController		m_Motion;			//アニメーション管理クラス
	float						m_PosX;				//位置Ｘ
	float						m_PosY;				//位置Ｙ
	bool						m_bMove;			//移動フラグ
	float						m_MoveX;			//速度Ｘ
	float						m_MoveY;			//速度Ｙ
	int							m_JumpCount;		//ジャンプカウント
	bool						m_bReverse;			//反転フラグ
	int							m_HP;				//HP
	int							m_DamageWait;		//無敵時間
	bool						m_bEnd;				//死亡フラグ
	CEffectManager*				m_pEffectManager;	//エフェクトマネージャー
	CEffect*					m_pEndEffect;		//エフェクト
	bool						m_bGoal;			//ゴールフラグ
	CRectangle					m_SrcRect;			//矩形

	//モーション種類定義
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMPSTART,
		MOTION_JUMPEND,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};
public:
	CPlayer();
	~CPlayer();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void UpdateKey(void);
	void UpdateMove(void);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	CRectangle GetRect() {
		return CRectangle(m_PosX + PLAYER_RECTDECREASE, m_PosY + PLAYER_RECTDECREASE, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE, m_PosY + m_SrcRect.GetHeight());
	}
	void CollisionStage(float ox, float oy);
	bool CollisionEnemy(CEnemy& ene);
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }
	bool IsEnd(void) { return m_bEnd; }
	bool CollisionItem(CItem& itm);
	bool IsGoal(void) { return m_bGoal; }
	int GetHP(void) { return m_HP; }
};

