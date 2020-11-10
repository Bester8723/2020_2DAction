/*************************************************************************//*!

					@file	StageTemplate.cpp
					@brief	�X�e�[�W�̃e���v���W�B

															@author	�r��@����
*//**************************************************************************/


//INCLUDE
#include "StageTemplate.h"


/*/////////////////////////////////////////////////////////////////////////
 *
 * �e�X�e�[�W��Load�֐��e���v���[�g
 *
 */////////////////////////////////////////////////////////////////////////

 /**
  * �ǂݍ���
  * ���p����e�N�X�`���ƃX�e�[�W�t�@�C����ǂݍ��ށB
  *
  * ����
  * [in]			pName				�X�e�[�W�t�@�C���̖��O
  */
bool CStageTemplate::LoadFile(	char* pName,
								CTexture* pChipTex, CTexture* pBackTex, float* pChipSize, int* pXcnt, int* pYcnt, char** pChipData,
								int* pEneTexCnt, CTexture** pEneTex, char** pEneData, int* pEneCnt,
								int* pItemTexCnt, CTexture** pItemTex, char** pItemData, int* pItemCnt,
								int* pHatenaTexCnt, CTexture** pHatenaTex, char** pHatenaData, int* pHatenaCnt	) {

	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y�������̃��������m�ۂ���
	char* pBuffer = (char*)malloc(fSize + 1);
	//�t�@�C�������ׂăo�b�t�@�ɓǂݍ���
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;


	//�}�b�v�̓ǂݍ���
	pstr = strtok(pBuffer, ",");
	if (!LoadMap(pstr, pChipTex, pBackTex, pChipSize, pXcnt, pYcnt, pChipData))							return FALSE;
	//�G�̓ǂݍ���
	pstr = strtok(NULL, ",");
	if (!LoadCategory(pstr, pEneTexCnt, pEneTex, pEneData, pEneCnt, pXcnt, pYcnt))						return FALSE;
	//�A�C�e���̓ǂݍ���
	pstr = strtok(NULL, ",");
	if (!LoadCategory(pstr, pItemTexCnt, pItemTex, pItemData, pItemCnt, pXcnt, pYcnt))					return FALSE;
	//�͂Ăȃu���b�N�̓ǂݍ���
	pstr = strtok(NULL, ",");
	if (!LoadCategory(pstr, pHatenaTexCnt, pHatenaTex, pHatenaData, pHatenaCnt, pXcnt, pYcnt))			return FALSE;


	//�t�@�C�������
	fclose(fp);
	free(pBuffer);

	return TRUE;
}

/**
 * �}�b�v�̓ǂݍ���
 * ���p����e�N�X�`���ƃX�e�[�W�t�@�C����ǂݍ��ށB
 *
 * ����
 * [in]			pMapStr				���p���镶����
 */
bool CStageTemplate::LoadMap(	char* pMapStr,
								CTexture* pChipTex, CTexture* pBackTex, float* pChipSize, int* pXcnt, int* pYcnt,
								char** pChipData) {
	//�e�N�X�`���̓ǂݍ���
	if (!pBackTex->Load(pMapStr))	return FALSE;
	pMapStr = strtok(NULL, ",");
	if (!pChipTex->Load(pMapStr))	return FALSE;

	//�`�b�v�T�C�Y
	*pChipSize = (float)atof(strtok(NULL, ","));

	//�}�b�v�̃`�b�v��
	*pXcnt = atoi(strtok(NULL, ","));
	*pYcnt = atoi(strtok(NULL, ","));

	//�}�b�v�`�b�v�p�̃��������m��
	*pChipData = (char*)malloc(*pXcnt * *pYcnt);

	//�`�b�v�f�[�^�̓ǂݍ���
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
 * �e�J�e�S���[�̓ǂݍ���
 * ���p����e�N�X�`���ƃX�e�[�W�t�@�C����ǂݍ��ށB
 *
 * ����
 * [in]			pCategoryStr				���p���镶����
 */
bool CStageTemplate::LoadCategory(	char* pCategoryStr,
									int* pTexCnt, CTexture** pTex, char** pData, int* pCnt,
									int* pXcnt, int* pYcnt) {
	//�e�N�X�`���̓ǂݍ���
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

	//�z�u�f�[�^�̓ǂݍ���
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
 * �e�X�e�[�W��Render�֐��e���v���[�g
 *
 */////////////////////////////////////////////////////////////////////////

 /**
  * �X�e�[�W�̕`��
  *
  *
  * ����
  * [in]			pMapStr				���p���镶����
  */
void CStageTemplate::RenderStage(	CTexture* pChipTex, float ChipSize, int Ycnt, int Xcnt, char* pChipData,
									float ScrollX, float ScrollY) {
	//�e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = pChipTex->GetWidth() / ChipSize;
	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < Ycnt; y++)
	{
		for (int x = 0; x < Xcnt; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ��O�͕`�悵�Ȃ�
			char cn = pChipData[y * Xcnt + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(ChipSize * (cn % tcx), ChipSize * (cn / tcx), ChipSize * (cn % tcx + 1), ChipSize * (cn / tcx + 1));
			//�}�b�v�`�b�v�̕`��
			pChipTex->Render(-ScrollX + x * ChipSize, -ScrollY + y * ChipSize, cr);
		}
	}
}