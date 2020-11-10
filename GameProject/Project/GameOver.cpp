/*************************************************************************//*!

					@file	GameOver.cpp
					@brief	ゲームオーバー画面。

															@author	池上　綾香
*//**************************************************************************/


//INCLUDE
#include	"GameOver.h"


/**
 * コンストラクタ
 *
 */
CGameOver::CGameOver() :
CSceneBase() {
}

/**
 * デストラクタ
 *
 */
CGameOver::~CGameOver() {
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGameOver::Load(void) {
	//テクスチャを読み込む
	if (!m_BackTexture.Load("GameOver.png"))		return FALSE;

	return TRUE;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGameOver::Initialize(void) {
	//読み込み
	Load();
	//フラグ類の初期化
	m_bEnd = false;
}

/**
 * 更新
 *
 */
void CGameOver::Update(void) {
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_TITLE;
	}
}

/**
 * 描画
 *
 */
void CGameOver::Render(void) {
	//テクスチャの描画
	m_BackTexture.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Press Enter Key");
}

/**
 * デバッグ描画
 *
 */
void CGameOver::RenderDebug(void) {
	//デバッグ描画
	CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_WHITE, "ゲームオーバー画面");
}

/**
 * 解放
 *
 */
void CGameOver::Release(void) {
	//テクスチャの解放
	m_BackTexture.Release();
}
