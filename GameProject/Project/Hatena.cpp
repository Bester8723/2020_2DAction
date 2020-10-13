#include "Hatena.h"

/**
 * �R���X�g���N�^
 *
 */
CHatena::CHatena() : 
m_pTexture(NULL),
m_PosX(0.0f),
m_PosY(0.0f),
m_MoveX(0.0f),
m_MoveY(0.0f),
m_bShow(false),
m_SrcRect() ,
m_bItem(false) {
}

/**
 * �f�X�g���N�^
 *
 */
CHatena::~CHatena()
{
	//delete[] �ŉ�������悤��Release���f�X�g���N�^�Ŏ��s����
	Release();
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 */
void CHatena::Initialize(float px, float py)
{
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bShow = true;
	m_bItem = true;
	m_SrcRect = CRectangle(0, 0, 32, 32);
}

/**
 * �X�V
 *
 */
void CHatena::Update(void)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}
	
}

/**
 * �v���C���[�Ƃ͂Ăȃu���b�N�̓�����
 *
 * ����
 * [in]				prec				�v���C���[�̋�`
 * [in]				pItem				������s���A�C�e��
 */
void CHatena::CollisionPlayer(CRectangle prec, CItem& pItem)
{
	//�͂Ăȃu���b�N�̒��ɃA�C�e�����Ȃ��Ƃ�
	if (!m_bItem)
	{
		return;
	}
	//�v���C���[��`�̐���
	CRectangle trec = prec;
	trec.Bottom = trec.Top + 1;
	trec.Top -= 2;
	trec.Left -= 2;
	trec.Right -= 2;
	//�͂Ăȃu���b�N�ƃv���C���[�̋�`���������Ă�����
	if (GetRect().CollisionRect(trec))
	{
		//�͂Ăȃu���b�N�Ɠ������Ă���A�C�e����T��
		if (GetRect().CollisionRect(pItem.GetRect()))
		{
			pItem.Drop();
			m_bItem = false;
			m_SrcRect = CRectangle(32, 0, 64, 32);
		}
	}
}

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CHatena::Render(float wx, float wy)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, m_SrcRect);
}

/**
 * ���
 *
 */
void CHatena::Release(void)
{
}
