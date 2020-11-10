/*************************************************************************//*!

					@file	GameClear.cpp
					@brief	�Q�[���N���A��ʁB

															@author	�r��@����
*//**************************************************************************/


//INCLUDE
#include	"GameClear.h"


/**
 * �R���X�g���N�^
 *
 */
CGameClear::CGameClear() :
CSceneBase() {
}

/**
 * �f�X�g���N�^
 *
 */
CGameClear::~CGameClear() {
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGameClear::Load(void) {
	//�e�N�X�`����ǂݍ���
	if (!m_BackTexture.Load("GameClear.png"))	return FALSE;

	return TRUE;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGameClear::Initialize(void) {
	//�ǂݍ���
	Load();
	//�t���O�ނ�������
	m_bEnd = false;
}

/**
 * �X�V
 *
 */
void CGameClear::Update(void) {
	//Enter�L�[�Ń^�C�g����ʂ�
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
void CGameClear::Render(void) {
	//�e�N�X�`���̕`��
	m_BackTexture.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Press Enter Key");
}

/**
 * �f�o�b�O�`��
 *
 */
void CGameClear::RenderDebug(void) {
	//�f�o�b�O�`��
	CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "�Q�[���N���A���");
}

/**
 * ���
 *
 */
void CGameClear::Release(void) {
	//�e�N�X�`���̉��
	m_BackTexture.Release();
}