/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

//�V�[���N���X
CSceneBase*				gpScene = NULL;


/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	//�ŏ��Ɏ��s�����V�[���̏�����
	gpScene = new CTitle();
	gpScene->Initialize();

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	//�V�[���̍X�V
	gpScene->Update();
	//�V�[�����I��������
	if (gpScene->IsEnd())
	{
		//���̃V�[�����擾
		int change = gpScene->GetNextScene();
		//�Â��V�[������������
		gpScene->Release();
		delete gpScene;
		//���̃V�[���ԍ��ɉ����ăV�[��������ď���������
		switch (change)
		{
		case SCENENO_TITLE:
			gpScene = new CTitle();
			break;
		case SCENENO_GAME:
			gpScene = new CGame();
			break;
		case SCENENO_GAMECLEAR:
			gpScene = new CGameClear();
			break;
		case SCENENO_GAMEOVER:
			gpScene = new CGameOver();
			break;
		}
		gpScene->Initialize();
	}

	//�f�o�b�O�\���̐؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		m_bDebug = ((m_bDebug) ? false : true);
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,0.0f,1.0f,1.0f,0);

	//�V�[���̕`��
	gpScene->Render();
	//�V�[���̃f�o�b�O�`��
	if (m_bDebug)
	{
		gpScene->RenderDebug();
	}

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void){
	//�V�[���̉��
	if (gpScene)
	{
		gpScene->Release();
		delete gpScene;
		gpScene = NULL;
	}
	return TRUE;
}