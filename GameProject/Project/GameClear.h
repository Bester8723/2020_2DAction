/*************************************************************************//*!

					@file	GameClear.h
					@brief	�Q�[���N���A��ʁB

															@author	�r��@����
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"SceneBase.h"
#include	"GameDefine.h"


class CGameClear : public CSceneBase {
private:

public:
	CGameClear();
	~CGameClear();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};
