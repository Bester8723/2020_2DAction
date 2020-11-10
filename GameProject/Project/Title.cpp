/*************************************************************************//*!

					@file	Title.cpp
					@brief	�^�C�g����ʁB

															@author	�r��@����
*//**************************************************************************/


//INCLUDE
#include	"Title.h"


/**
 * �R���X�g���N�^
 *
 */
CTitle::CTitle() :
CSceneBase() {
}

/**
 * �f�X�g���N�^
 *
 */
CTitle::~CTitle() {
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CTitle::Load(void) {
	//�w�i�e�N�X�`����ǂݍ���
	if (!m_BackTexture.Load("Title.png"))	return FALSE;

	return TRUE;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CTitle::Initialize(void) {
	//�ǂݍ���
	Load();
	//�t���O�ނ̏�����
	m_bEnd = false;
}

/**
 * �X�V
 *
 */
void CTitle::Update(void) {
	//Enter�L�[�ŃQ�[����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAME;
	}
}

/**
 * �`��
 *
 */
void CTitle::Render(void) {
	//�w�i�F�̕ύX
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_COLOR_WHITE);
	//�e�N�X�`���̕`��
	m_BackTexture.Render(0, 200);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_BLACK, "Press Enter Key");
}

/**
 * �f�o�b�O�`��
 *
 */
void CTitle::RenderDebug(void) {
	//�f�o�b�O�`��
	CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "�^�C�g�����");
}

/**
 * ���
 *
 */
void CTitle::Release(void) {
	//�e�N�X�`���̉��
	m_BackTexture.Release();
}