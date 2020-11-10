/*************************************************************************//*!

					@file	GameOver.cpp
					@brief	�Q�[���I�[�o�[��ʁB

															@author	�r��@����
*//**************************************************************************/


//INCLUDE
#include	"GameOver.h"


/**
 * �R���X�g���N�^
 *
 */
CGameOver::CGameOver() :
CSceneBase() {
}

/**
 * �f�X�g���N�^
 *
 */
CGameOver::~CGameOver() {
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGameOver::Load(void) {
	//�e�N�X�`����ǂݍ���
	if (!m_BackTexture.Load("GameOver.png"))		return FALSE;

	return TRUE;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGameOver::Initialize(void) {
	//�ǂݍ���
	Load();
	//�t���O�ނ̏�����
	m_bEnd = false;
}

/**
 * �X�V
 *
 */
void CGameOver::Update(void) {
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_TITLE;
	}
}

/**
 * �`��
 *
 */
void CGameOver::Render(void) {
	//�e�N�X�`���̕`��
	m_BackTexture.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Press Enter Key");
}

/**
 * �f�o�b�O�`��
 *
 */
void CGameOver::RenderDebug(void) {
	//�f�o�b�O�`��
	CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_WHITE, "�Q�[���I�[�o�[���");
}

/**
 * ���
 *
 */
void CGameOver::Release(void) {
	//�e�N�X�`���̉��
	m_BackTexture.Release();
}
