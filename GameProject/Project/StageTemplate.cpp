/*************************************************************************//*!

					@file	StageTemplate.cpp
					@brief	ステージのテンプレ集。

															@author	池上　綾香
*//**************************************************************************/


//INCLUDE
#include "StageTemplate.h"


/*/////////////////////////////////////////////////////////////////////////
 *
 * 各ステージのLoad関数テンプレート
 *
 */////////////////////////////////////////////////////////////////////////

 /**
  * 読み込み
  * 利用するテクスチャとステージファイルを読み込む。
  *
  * 引数
  * [in]			pName				ステージファイルの名前
  */
bool CStageTemplate::LoadFile(	char* pName,
								CTexture* pChipTex, CTexture* pBackTex, float* pChipSize, int* pXcnt, int* pYcnt, char** pChipData,
								int* pEneTexCnt, CTexture** pEneTex, char** pEneData, int* pEneCnt,
								int* pItemTexCnt, CTexture** pItemTex, char** pItemData, int* pItemCnt,
								int* pHatenaTexCnt, CTexture** pHatenaTex, char** pHatenaData, int* pHatenaCnt	) {

	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルをすべてバッファに読み込む
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;


	//マップの読み込み
	pstr = strtok(pBuffer, ",");
	if (!LoadMap(pstr, pChipTex, pBackTex, pChipSize, pXcnt, pYcnt, pChipData))							return FALSE;
	//敵の読み込み
	pstr = strtok(NULL, ",");
	if (!LoadCategory(pstr, pEneTexCnt, pEneTex, pEneData, pEneCnt, pXcnt, pYcnt))						return FALSE;
	//アイテムの読み込み
	pstr = strtok(NULL, ",");
	if (!LoadCategory(pstr, pItemTexCnt, pItemTex, pItemData, pItemCnt, pXcnt, pYcnt))					return FALSE;
	//はてなブロックの読み込み
	pstr = strtok(NULL, ",");
	if (!LoadCategory(pstr, pHatenaTexCnt, pHatenaTex, pHatenaData, pHatenaCnt, pXcnt, pYcnt))			return FALSE;


	//ファイルを閉じる
	fclose(fp);
	free(pBuffer);

	return TRUE;
}

/**
 * マップの読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			pMapStr				利用する文字列
 */
bool CStageTemplate::LoadMap(	char* pMapStr,
								CTexture* pChipTex, CTexture* pBackTex, float* pChipSize, int* pXcnt, int* pYcnt,
								char** pChipData) {
	//テクスチャの読み込み
	if (!pBackTex->Load(pMapStr))	return FALSE;
	pMapStr = strtok(NULL, ",");
	if (!pChipTex->Load(pMapStr))	return FALSE;

	//チップサイズ
	*pChipSize = (float)atof(strtok(NULL, ","));

	//マップのチップ数
	*pXcnt = atoi(strtok(NULL, ","));
	*pYcnt = atoi(strtok(NULL, ","));

	//マップチップ用のメモリを確保
	*pChipData = (char*)malloc(*pXcnt * *pYcnt);

	//チップデータの読み込み
	for (int y = 0; y < *pYcnt; y++)
	{
		for (int x = 0; x < *pXcnt; x++)
		{
			(*pChipData)[y * *pXcnt + x] = atoi(strtok(NULL, ","));
		}
	}

	return TRUE;
}

/**
 * 各カテゴリーの読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			pCategoryStr				利用する文字列
 */
bool CStageTemplate::LoadCategory(	char* pCategoryStr,
									int* pTexCnt, CTexture** pTex, char** pData, int* pCnt,
									int* pXcnt, int* pYcnt) {
	//テクスチャの読み込み
	*pTexCnt = atoi(pCategoryStr);
	*pTex = new CTexture[*pTexCnt];
	for (int i = 0; i < *pTexCnt; i++)
	{
		pCategoryStr = strtok(NULL, ",");
		if (!(*pTex)[i].Load(pCategoryStr))
		{
			return FALSE;
		}
	}

	//配置データの読み込み
	*pData = (char*)malloc(*pXcnt * *pYcnt);
	*pCnt = 0;
	for (int y = 0; y < *pYcnt; y++)
	{
		for (int x = 0; x < *pXcnt; x++)
		{
			(*pData)[y * *pXcnt + x] = atoi(strtok(NULL, ","));
			if ((*pData)[y * *pXcnt + x] > 0)
			{
				*pCnt += 1;
			}
		}
	}

	return TRUE;
}


/*/////////////////////////////////////////////////////////////////////////
 *
 * 各ステージのRender関数テンプレート
 *
 */////////////////////////////////////////////////////////////////////////

 /**
  * ステージの描画
  *
  *
  * 引数
  * [in]			pMapStr				利用する文字列
  */
void CStageTemplate::RenderStage(	CTexture* pChipTex, float ChipSize, int Ycnt, int Xcnt, char* pChipData,
									float ScrollX, float ScrollY) {
	//テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = pChipTex->GetWidth() / ChipSize;
	//マップチップの描画
	for (int y = 0; y < Ycnt; y++)
	{
		for (int x = 0; x < Xcnt; x++)
		{
			//描画するチップ番号
			//チップ番号０は描画しない
			char cn = pChipData[y * Xcnt + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(ChipSize * (cn % tcx), ChipSize * (cn / tcx), ChipSize * (cn % tcx + 1), ChipSize * (cn / tcx + 1));
			//マップチップの描画
			pChipTex->Render(-ScrollX + x * ChipSize, -ScrollY + y * ChipSize, cr);
		}
	}
}