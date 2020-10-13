#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"Enemy.h"
#include	"EffectManager.h"
#include	"Item.h"

//�ړ����x
#define		PLAYER_SPEED			0.4f

//�ړ��ő呬�x
#define		PLAYER_MAXSPEED			8.0f

//�W�����v���x
#define		PLAYER_JUMP				-13.0f

//�����蔻�茸����
#define		PLAYER_RECTDECREASE		12

class CPlayer
{
private:
	CTexture					m_Texture;			//�e�N�X�`��
	CSpriteMotionController		m_Motion;			//�A�j���[�V�����Ǘ��N���X
	float						m_PosX;				//�ʒu�w
	float						m_PosY;				//�ʒu�x
	bool						m_bMove;			//�ړ��t���O
	float						m_MoveX;			//���x�w
	float						m_MoveY;			//���x�x
	int							m_JumpCount;		//�W�����v�J�E���g
	bool						m_bReverse;			//���]�t���O
	int							m_HP;				//HP
	int							m_DamageWait;		//���G����
	bool						m_bEnd;				//���S�t���O
	CEffectManager*				m_pEffectManager;	//�G�t�F�N�g�}�l�[�W���[
	CEffect*					m_pEndEffect;		//�G�t�F�N�g
	bool						m_bGoal;			//�S�[���t���O
	CRectangle					m_SrcRect;			//��`

	//���[�V������ޒ�`
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

