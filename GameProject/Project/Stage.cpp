/*************************************************************************//*!

					@file	Stage.cpp
					@brief	�X�e�[�W�B

															@author	�r��@����
*//**************************************************************************/


//INCLUDE
#include	"Stage.h"
#include	<sys/stat.h>


/**
 * �R���X�g���N�^
 *
 */
CStage::CStage() :
m_ChipTexture(),
m_BackTexture(),
m_ChipSize(0),
m_XCount(0),
m_YCount(0),
m_pChipData(NULL),
m_ScrollX(0),
m_ScrollY(0),
m_EnemyTextureCount(0),
m_pEnemyTexture(NULL),
m_EnemyCount(0),
m_ItemTextureCount(0),
m_pItemTexture(NULL),
m_ItemCount(0),
m_HatenaTextureCount(0),
m_pHatenaTexture(NULL),
m_HatenaCount(0) {
}

/**
 * �f�X�g���N�^
 *
 */
CStage::~CStage() {
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`���ƃX�e�[�W�t�@�C����ǂݍ��ށB
 *
 * ����
 * [in]			pName				�X�e�[�W�t�@�C���̖��O
 */
bool CStage::Load(char* pName) {
	//�X�e�[�W�̓ǂݍ���
	if (!m_StageTpl.LoadFile(	"Stage.txt",
								&m_ChipTexture, &m_BackTexture, &m_ChipSize, &m_XCount, &m_YCount, &m_pChipData,
								&m_EnemyTextureCount, &m_pEnemyTexture, &m_pEnemyData, &m_EnemyCount,
								&m_ItemTextureCount, &m_pItemTexture, &m_pItemData, &m_ItemCount,
								&m_HatenaTextureCount, &m_pHatenaTexture, &m_pHatenaData, &m_HatenaCount))	return FALSE;

	return TRUE;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 */
void CStage::Initialize(CEnemy* pEnemy, CItem* pItem, CHatena* pHatena) {
	m_ScrollX = 0;
	m_ScrollY = 0;

	//�G�̏�����
	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ��O�͔z�u���Ȃ�
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on]);
			pEnemy[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
	//�A�C�e���̏�����
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ��O�͔z�u���Ȃ�
			char on = m_pItemData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pItem[n].SetTexture(&m_pItemTexture[on]);
			pItem[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
	//�͂Ăȃu���b�N�̏�����
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ��O�͔z�u���Ȃ�
			char on = m_pHatenaData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pHatena[n].SetTexture(&m_pHatenaTexture[on]);
			pHatena[n++].Initialize(x * m_ChipSize, y * m_ChipSize);
		}
	}
}

/**
 * �X�V
 *
 * ����
 * [in]				pl					�v���C���[�A�X�N���[���̔���Ɏg�p
 */
void CStage::Update(CPlayer& pl) {
	//�v���C���[�̋�`���擾
	CRectangle prec = pl.GetRect();
	//�X�N���[���̕�
	float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	//�X�e�[�W�S�̂̕�
	float stgw = m_ChipSize * m_XCount;
	//���W����ʒ[�ɂ���Ă���i�e�[����400pixel�j�ꍇ�A�X�N���[�����s���ĕ␳����
	if (prec.Left - m_ScrollX < 400)
	{
		m_ScrollX -= 400 - (prec.Left - m_ScrollX);
		if (m_ScrollX <= 0)
		{
			m_ScrollX = 0;
		}
	}
	else if (prec.Right - m_ScrollX > sw - 400)
	{
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - 400);
		if (m_ScrollX >= stgw - sw)
		{
			m_ScrollX = stgw - sw;
		}
	}
}

/**
 * �`��
 *
 */
void CStage::Render(void) {
	//���i�̕`��
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-m_ScrollY % hn) - hn; y < sch; y += hn)
	{
		for (float x = ((int)-m_ScrollX % wn) - wn; x < scw; x += wn)
		{
			m_BackTexture.Render(x, y);
		}
	}

	//�e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ��O�͕`�悵�Ȃ�
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize * (cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//�}�b�v�`�b�v�̕`��
			m_ChipTexture.Render(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize, cr);
		}
	}
}

/**
 * �f�o�b�O�`��
 *
 */
void CStage::RenderDebug(void) {
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10, 100, "�X�N���[�� X : %.0f , Y : %.0f", m_ScrollX, m_ScrollY);
}

/**
 * ���
 *
 */
void CStage::Release(void) {
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
	if (m_pEnemyData)
	{
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pEnemyTexture)
	{
		delete[] m_pEnemyTexture;
		m_pEnemyTexture = NULL;
	}
	if (m_pItemData)
	{
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pItemTexture)
	{
		delete[] m_pItemTexture;
		m_pItemTexture = NULL;
	}
	if (m_pHatenaData)
	{
		free(m_pHatenaData);
		m_pHatenaData = NULL;
	}
	if (m_pHatenaTexture)
	{
		delete[] m_pHatenaTexture;
		m_pHatenaTexture = NULL;
	}
}

/**
 * �����蔻��
 *
 * ����
 * [in]			r			�����`
 * [out]		ox			�w���܂�
 * [out]		oy			�x���܂�
 */
bool CStage::Collision(CRectangle r, float& ox, float& oy)
{
	bool re = false;

	//�����蔻�肷���`�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;
	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	//�����蔻��������`�̍��ォ��E���͈̔͂̂ݓ����蔻��������Ȃ�
	//����ȊO�̔ԍ��͓����邱�Ƃ͂Ȃ��̂ŁA���肪�K�v�Ȃ�
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ��O�͓����蔻�肵�Ȃ�
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//�����蔻��p�̃L�����N�^��`
			//���Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;		//���̋�`�͏㑤�����Ɠ����l�ɂ���
			brec.Expansion(-6, 0);				//���͈̔͂��������߂�
			//���Ɠ����蔻��
			if (cr.CollisionRect(brec))
			{
				re = true;
				//���̖��܂�Ȃ̂ŁA�`�b�v��[�����`�̉��[�̒l���������l�����܂�̒l
				oy += cr.Top - brec.Bottom;
				r.Top += cr.Top - brec.Bottom;
				r.Bottom += cr.Top - brec.Bottom;
			}

			//�����蔻��p�̃L�����N�^��`
			//���A�E���ꂼ��Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;		//���̋�`�͉E�������Ɠ����l�ɂ���
			lrec.Expansion(0, -6);				//�c�͈̔͂��������߂�
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;		//�E�̋�`�͍������E�Ɠ����l�ɂ���
			rrec.Expansion(0, -6);				//�c�͈̔͂��������߂�
			//���Ɠ����蔻��
			if (cr.CollisionRect(lrec))
			{
				re = true;
				//���̖��܂�Ȃ̂ŁA�`�b�v�E�[�����`�̍��[�̒l���������l�����܂�̒l
				ox += cr.Right - lrec.Left;
				r.Left += cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//�E�Ɠ����蔻��
			else if (cr.CollisionRect(rrec))
			{
				re = true;
				//�E�̖��܂�Ȃ̂ŁA�`�b�v���[�����`�̉E���̒l���������l�����܂�̒l
				ox += cr.Left - rrec.Right;
				r.Left += cr.Left - rrec.Right;
				r.Right += cr.Left - rrec.Right;
			}
			//�����蔻��p�̃L�����N�^��`
			//��Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;		//��̋�`�͉�������Ɠ����l�ɂ���
			trec.Expansion(-6, 0);				//���͈̔͂��������߂�
			//��Ɠ����蔻��
			if (cr.CollisionRect(trec))
			{
				re = true;
				//��̖��܂�Ȃ̂ŁA�`�b�v���[�����`�̏�[�̒l���������l�����܂�̒l
				oy += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}
		}
	}

	return re;
}
