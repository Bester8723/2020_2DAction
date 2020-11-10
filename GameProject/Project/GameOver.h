/*************************************************************************//*!

					@file	GameOver.h
					@brief	ゲームオーバー画面。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
//INCLUDE
#include	"SceneBase.h"
#include	"GameDefine.h"


class CGameOver : public CSceneBase {
private:

public:
	CGameOver();
	~CGameOver();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

