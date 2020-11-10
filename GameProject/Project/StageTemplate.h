/*************************************************************************//*!

					@file	StageTemplate.h
					@brief	ステージのテンプレ集。

															@author	池上　綾香
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
	 * 各ステージのLoad関数テンプレート
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
	 * 各ステージのRender関数テンプレート
	 *
	 *****************************************************/
	void RenderStage(CTexture* pChipTex, float ChipSize, int Ycnt, int Xcnt, char* pChipData, float ScrollX, float ScrollY);
};