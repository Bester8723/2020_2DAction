/*************************************************************************//*!

					@file	Stage.h
					@brief	ステージ。

															@author	池上　綾香
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"Player.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"Hatena.h"
#include	"StageTemplate.h"


class CStage
{
private:
	CStageTemplate			m_StageTpl;				//ステージテンプレ

	float					m_ScrollX;				//Ｘ軸のスクロール値
	float					m_ScrollY;				//Ｙ軸のスクロール値

	CTexture				m_ChipTexture;			//マップチップのテクスチャ
	CTexture				m_BackTexture;			//背景のテクスチャ

	float					m_ChipSize;				//マップチップのサイズ
	int						m_XCount;				//Ｘ軸のチップ数
	int						m_YCount;				//Ｙ軸のチップ数
	char*					m_pChipData;			//マップチップデータのポインタ

	int						m_EnemyTextureCount;	//敵のテクスチャの枚数
	CTexture*				m_pEnemyTexture;		//敵のテクスチャのポインタ
	char*					m_pEnemyData;			//敵のマップチップデータのポインタ
	int						m_EnemyCount;			//敵の配置数

	int						m_ItemTextureCount;		//アイテムのテクスチャの枚数
	CTexture*				m_pItemTexture;			//アイテムのテクスチャのポインタ
	char*					m_pItemData;			//アイテムのマップチップデータのポインタ
	int						m_ItemCount;			//アイテムの配置数

	int						m_HatenaTextureCount;	//はてなブロックのテクスチャの枚数
	CTexture*				m_pHatenaTexture;		//はてなブロックのテクスチャのポインタ
	char*					m_pHatenaData;			//はてなブロックのマップチップデータのポインタ
	int						m_HatenaCount;			//はてなブロックの配置数

public:
	CStage();
	~CStage();
	bool Load(char* pName);
	void Initialize(CEnemy* pEnemy, CItem* pItem, CHatena* pHatena);
	void Update(CPlayer& pl);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	float GetScrollX() { return m_ScrollX; }
	float GetScrollY() { return m_ScrollY; }
	bool Collision(CRectangle r, float& ox, float& oy);
	int GetEnemyCount() { return m_EnemyCount; }
	int GetItemCount() { return m_ItemCount; }
	int GetHatenaCount() { return m_HatenaCount; }
};

