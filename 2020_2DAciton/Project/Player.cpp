#include "Player.h"

/**
 * �R���X�g���N�^
 *
 */
CPlayer::CPlayer() :
	m_Texture(),
	m_Motion(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_bMove(false),
	m_MoveX(0.0f),
	m_MoveY(0.0f),
	m_JumpCount(0),
	m_bReverse(false),
	m_HP(0),
	m_SrcRect() {
}

/**
 * �f�X�g���N�^
 *
 */
CPlayer::~CPlayer()
{
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CPlayer::Load(void)
{
	//�e�N�X�`���̓ǂݍ���
	if (!m_Texture.Load("player.png"))
	{
		return false;
	}

	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		{
			"�ҋ@",
			0,0,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"�ړ�",
			0,70,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
		},
		{
			"�W�����v�㏸",
			0,140,
			60,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"�W�����v���~",
			240,140,
			60,64,
			FALSE,{{2,0,0},{2,1,0}}
		},
		{
			"�_���[�W",
			480,0,
			60,64,
			FALSE,{{20,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);

	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * �v���C���[�̈ʒu�ȂǏ�Ԃ��������������Ƃ��Ɏ��s����B
 */
void CPlayer::Initialize(void)
{
	m_PosX = 20;
	m_PosY = 640 - m_Motion.GetSrcRect().GetHeight();
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_JumpCount = 0;
	m_HP = 2;
	m_DamageWait = 0;
	m_bEnd = false;
	m_pEndEffect = NULL;
	m_bGoal = false;
	m_Motion.ChangeMotion(MOTION_WAIT);
}

/**
 * �X�V
 *
 */
void CPlayer::Update(void)
{
	//HP���Ȃ��Ȃ�Ɣ����̏I����ҋ@���ďI��
	if (m_HP <= 0)
	{
		if (!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bEnd = true;
		}
		return;
	}
	//�ړ��t���O�A���̃t���[���ł̈ړ�������������ۑ�
	m_bMove = false;
	//�W�����v���~�ւ̐؂�ւ�
	if (m_Motion.GetMotionNo() == MOTION_JUMPSTART && m_MoveY >= 0)
	{
		m_Motion.ChangeMotion(MOTION_JUMPEND);
	}
	//���n�̏ꍇ�̓���
	if (m_Motion.GetMotionNo() == MOTION_JUMPEND)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion() && m_MoveY == 0)
		{
			m_JumpCount = 0;
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//�_���[�W���̓���
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else
	{
		//�L�[���͂ɂ�鑀��
		UpdateKey();
	}
	//�ړ��X�V
	UpdateMove();
	//���ۂɍ��W���ړ�������
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;
	//��ʊO�ŗ����Ƃ���HP���O�ɂ���
	if (m_PosY >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION02);
	}
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

/**
 * �L�[���͂ɂ�铮��X�V
 *
 */
void CPlayer::UpdateKey(void)
{
	//�L�[�{�[�h�ł̈ړ�
	//���͂Œ��ڍ��W�𓮂����̂ł͂Ȃ��A���x��ω�������B
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_MoveX -= PLAYER_SPEED;
		m_bReverse = true;
		m_bMove = true;
		if (m_MoveX < -PLAYER_MAXSPEED)
		{
			m_MoveX = -PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_MoveX += PLAYER_SPEED;
		m_bReverse = false;
		m_bMove = true;
		if (m_MoveX > PLAYER_MAXSPEED)
		{
			m_MoveX = PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	//��L�[�ŃW�����v
	if (g_pInput->IsKeyPush(MOFKEY_UP) && m_JumpCount < 2)
	{
		//�W�����v�񐔂ɂ���đ��x�ω�
		switch (m_JumpCount)
		{
		case 0:	m_MoveY = PLAYER_JUMP;
			break;
		case 1: m_MoveY = PLAYER_JUMP * 0.8f;
			break;
		}
		m_JumpCount++;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
	}
}

/**
 * �ړ��X�V
 *
 */
void CPlayer::UpdateMove(void)
{
	//���̃t���[���ł̈ړ����͂��Ȃ���Ό������������s����
	if (!m_bMove)
	{
		if (m_MoveX > 0)
		{
			m_MoveX -= PLAYER_SPEED * 1.3f;
			if (m_MoveX <= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_MoveX < 0)
		{
			m_MoveX += PLAYER_SPEED * 1.3f;
			if (m_MoveX >= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//�d�͂ɂ�艺�ɏ�����������
	if (!g_pInput->IsKeyHold(MOFKEY_UP))
	{
		m_MoveY += GRAVITY * 2;
	}
	else 
	{
		m_MoveY += GRAVITY;
	}
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
}

/**
 * �`��
 *
 * ����
 * [in]					wx				���[���h�̕ω�
 * [in]					wy				���[���h�̕ω�
 */
void CPlayer::Render(float wx, float wy)
{
	//�C���^�[�o���Q�@�t���[�����Ƃɕ`������Ȃ�
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}
	//�`���`
	CRectangle dr = m_SrcRect;
	//�`��ʒu
	float px = m_PosX - wx;
	float py = m_PosY - wy;
	//���]�t���O�� ON �̏ꍇ�A�`���`�𔽓]������
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//�e�N�X�`���̕`��
	m_Texture.Render(px, py, dr);
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]					wx				���[���h�̕ω�
 * [in]					wy				���[���h�̕ω�
 */
void CPlayer::RenderDebug(float wx, float wy)
{
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10, 70, "�v���C���[�ʒu X : %.0f , Y : %.0f", m_PosX, m_PosY);
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	//�͂Ăȃu���b�N�Ƃ̓����蔻��
	hr.Bottom = hr.Top + 1;
	hr.Top -= 2;
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 255));
}

/**
 * ���
 *
 */
void CPlayer::Release(void)
{
	m_Texture.Release();
	m_Motion.Release();
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]				ox				�w���܂��
 * [in]				oy				�x���܂��
 */
void CPlayer::CollisionStage(float ox, float oy)
{
	//���܂�������߂�
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
		if (m_JumpCount != 0)
		{
			m_JumpCount = 0;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

/**
 * �����蔻��
 * �����̓G�ɑ΂��ċ�`���m�̓����蔻������s����B
 * �������Ă����ꍇ�̓v���C���[�̏�Ԃ�ύX����B
 *
 * ����
 * [in]				ene				������s���G
 *
 * �߂�l
 * �������Ă���ꍇ��true�A�������Ă��Ȃ����false��Ԃ�
 */
bool CPlayer::CollisionEnemy(CEnemy& ene)
{
	if (!ene.GetShow())
	{
		return false;
	}
	//HP���Ȃ��Ȃ�Ɠ����蔻�肵�Ȃ�
	if (m_HP <= 0)
	{
		return false;
	}
	//�_���[�W���̂��߁A�����蔻����s��Ȃ�
	if (m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}
	//�G�̋�`�Ǝ����̋�`�Ń_���[�W
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();
	if (prec.CollisionRect(erec))
	{
		//���݂����͓G�Ƀ_���[�W
		if (m_MoveY > 0)
		{
			ene.Damage(10, m_bReverse);
		}
		else
		{
			m_HP--;
			m_DamageWait = 60;
			if (prec.Left < erec.Left)
			{
				m_MoveX = -5.0f;
				m_bReverse = false;
			}
			else
			{
				m_MoveX = 5.0f;
				m_bReverse = true;
			}
			m_Motion.ChangeMotion(MOTION_DAMAGE);
			if (m_HP <= 0)
			{
				//�����G�t�F�N�g�𔭐�������
				m_pEndEffect = m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION02);
			}
			else
			{
				//�_���[�W�G�t�F�N�g�𔭐�������
				m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_DAMAGE);
			}
		}

		return true;
	}

	return false;
}

/**
* �����蔻��
* �����̃A�C�e���ɑ΂��ċ�`���m�̓����蔻������s����B
* �������Ă����ꍇ�̓v���C���[�̏�Ԃ�ύX����B
*
* ����
* [in]				itm				������s���A�C�e��
*
* �߂�l
* �������Ă���ꍇ��true�A�������Ă��Ȃ����false��Ԃ�
*/
bool CPlayer::CollisionItem(CItem & itm)
{
	if (!itm.GetShow() || !itm.GetCollision())
	{
		return false;
	}
	//�A�C�e���̋�`�Ǝ����̋�`�œ����蔻��
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	//�A�C�e���̃^�C�v���S�[���ł���ꍇ�A�����蔻������߂�
	if (itm.GetType() == ITEM_GOAL)
	{
		irec.Right -= 5;
		irec.Left += 5;
	}
	//�v���C���[�ƃA�C�e���̓�����
	if (prec.CollisionRect(irec))
	{
		//�A�C�e�����\���ɂ���
		itm.SetShow(false);
		//�A�C�e���̃^�C�v�ɂ���Č��ʂ�ς���
		switch (itm.GetType())
		{
		case ITEM_RECOVER:
			m_HP++;
			break;
		case ITEM_GOAL:
			m_bGoal = true;
			break;
		}
		return true;
	}
	return false;
}
