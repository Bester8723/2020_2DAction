/*************************************************************************//*!

					@file	Title.h
					@brief	タイトル画面。

															@author	池上　綾香
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