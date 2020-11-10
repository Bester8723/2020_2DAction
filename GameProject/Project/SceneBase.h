/*************************************************************************//*!

					@file	SceneBase.h
					@brief	�V�[����b�B

															@author	�r��@����
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"MOF.h"


class CSceneBase {
protected:
	bool				m_bEnd;						//�V�[���I���t���O
	int					m_NextScene;				//���̃V�[��
	CTexture			m_BackTexture;				//�w�i�e�N�X�`��
	
public:
	//�R���X�g���N�^
	CSceneBase() :
		m_bEnd(false),
		m_NextScene(0), 
		m_BackTexture() {
	}
	virtual ~CSceneBase() {};
	virtual bool Load(void) = 0;
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
	virtual void RenderDebug(void) = 0;
	virtual void Release(void) = 0;
	//���̃V�[�����擾
	int GetNextScene(void) { return m_NextScene; }
	//�V�[���͏I��������
	bool IsEnd(void) { return m_bEnd; }
};