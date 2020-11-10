/*************************************************************************//*!

					@file	Stage.h
					@brief	�X�e�[�W�B

															@author	�r��@����
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
	CStageTemplate			m_StageTpl;				//�X�e�[�W�e���v��

	float					m_ScrollX;				//�w���̃X�N���[���l
	float					m_ScrollY;				//�x���̃X�N���[���l

	CTexture				m_ChipTexture;			//�}�b�v�`�b�v�̃e�N�X�`��
	CTexture				m_BackTexture;			//�w�i�̃e�N�X�`��

	float					m_ChipSize;				//�}�b�v�`�b�v�̃T�C�Y
	int						m_XCount;				//�w���̃`�b�v��
	int						m_YCount;				//�x���̃`�b�v��
	char*					m_pChipData;			//�}�b�v�`�b�v�f�[�^�̃|�C���^

	int						m_EnemyTextureCount;	//�G�̃e�N�X�`���̖���
	CTexture*				m_pEnemyTexture;		//�G�̃e�N�X�`���̃|�C���^
	char*					m_pEnemyData;			//�G�̃}�b�v�`�b�v�f�[�^�̃|�C���^
	int						m_EnemyCount;			//�G�̔z�u��

	int						m_ItemTextureCount;		//�A�C�e���̃e�N�X�`���̖���
	CTexture*				m_pItemTexture;			//�A�C�e���̃e�N�X�`���̃|�C���^
	char*					m_pItemData;			//�A�C�e���̃}�b�v�`�b�v�f�[�^�̃|�C���^
	int						m_ItemCount;			//�A�C�e���̔z�u��

	int						m_HatenaTextureCount;	//�͂Ăȃu���b�N�̃e�N�X�`���̖���
	CTexture*				m_pHatenaTexture;		//�͂Ăȃu���b�N�̃e�N�X�`���̃|�C���^
	char*					m_pHatenaData;			//�͂Ăȃu���b�N�̃}�b�v�`�b�v�f�[�^�̃|�C���^
	int						m_HatenaCount;			//�͂Ăȃu���b�N�̔z�u��

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

