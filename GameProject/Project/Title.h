/*************************************************************************//*!

					@file	Title.h
					@brief	�^�C�g����ʁB

															@author	�r��@����
*//**************************************************************************/
#pragma once
//INCLUDE
#include	"SceneBase.h"
#include	"GameDefine.h"


class CTitle : public CSceneBase {
private:

public:
	CTitle();
	~CTitle();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};