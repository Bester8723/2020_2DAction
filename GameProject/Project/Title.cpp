/*************************************************************************//*!

					@file	Title.cpp
					@brief	タイトル画面。

															@author	池上　綾香
*//**************************************************************************/


//INCLUDE
#include	"Title.h"


/**
 * コンストラクタ
 *
 */
CTitle::CTitle() :
CSceneBase() {
}

/**
 * デストラクタ
 *
 */
CTitle::~CTitle() {
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CTitle::Load(void) {
	//背景テクスチャを読み込む
	if (!m_BackTexture.Load("Title.png"))	return FALSE;

	return TRUE;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CTitle::Initialize(void) {
	//読み込み
	Load();
	//フラグ類の初期化
	m_bEnd = false;
}

/**
 * 更新
 *
 */
void CTitle::Update(void) {
	//Enterキーでゲーム画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAME;
	}
}

/**
 * 描画
 *
 */
void CTitle::Render(void) {
	//背景色の変更
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_COLOR_WHITE);
	//テクスチャの描画
	m_BackTexture.Render(0, 200);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_BLACK, "Press Enter Key");
}

/**
 * デバッグ描画
 *
 */
void CTitle::RenderDebug(void) {
	//デバッグ描画
	CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "タイトル画面");
}

/**
 * 解放
 *
 */
void CTitle::Release(void) {
	//テクスチャの解放
	m_BackTexture.Release();
}