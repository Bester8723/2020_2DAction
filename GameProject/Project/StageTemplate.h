/*************************************************************************//*!

					@file	StageTemplate.h
					@brief	�X�e�[�W�̃e���v���W�B

															@author	�r��@����
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"Mof.h"


class CStageTemplate
{
private:

public:
	/*****************************************************
	 *
	 * �e�X�e�[�W��Load�֐��e���v���[�g
	 *
	 *****************************************************/
	bool LoadFile(	char* pName,
					CTexture* pChipTex, CTexture* pBackTex, float* pChipSize, int* pXcnt, int* pYcnt, char** pChipData,
					int* pEneTexCnt, CTexture** pEneTex, char** pEneData, int* pEneCnt,
					int* pItemTexCnt, CTexture** pItemTex, char** pItemData, int* pItemCnt,
					int* pHatenaTexCnt, CTexture** pHatenaTex, char** pHatenaData, int* pHatenaCn	);
	bool LoadMap(char* pMapStr, CTexture* pChipTex, CTexture* pBackTex, float* pChipSize, int* pXcnt, int* pYcnt, char** pChipData);
	bool LoadCategory(char* pCategoryStr, int* pTexCnt, CTexture** pTex, char** pData, int* pCnt, int* pXcnt, int* pYcnt);

	/*****************************************************
	 *
	 * �e�X�e�[�W��Render�֐��e���v���[�g
	 *
	 *****************************************************/
	void RenderStage(CTexture* pChipTex, float ChipSize, int Ycnt, int Xcnt, char* pChipData, float ScrollX, float ScrollY);
};