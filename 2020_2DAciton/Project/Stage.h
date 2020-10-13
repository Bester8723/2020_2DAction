#pragma once

#include	"Player.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"Hatena.h"


class CStage
{
private:
	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;

	float					m_ChipSize;
	int						m_XCount;
	int						m_YCount;
	char*					m_pChipData;

	float					m_ScrollX;
	float					m_ScrollY;

	int						m_EnemyTextureCount;
	CTexture*				m_pEnemyTexture;
	char*					m_pEnemyData;
	int						m_EnemyCount;

	int						m_ItemTextureCount;
	CTexture*				m_pItemTexture;
	char*					m_pItemData;
	int						m_ItemCount;

	int						m_HatenaTextureCount;
	CTexture*				m_pHatenaTexture;
	char*					m_pHatenaData;
	int						m_HatenaCount;
public:
	CStage();
	~CStage();
	bool Load(char* pName);
	bool LoadMap(char* pMapStr);
	bool LoadEnemy(char* pEnemyStr);
	bool LoadItem(char* pItemStr);
	bool LoadHatena(char* pHatenaStr);
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

