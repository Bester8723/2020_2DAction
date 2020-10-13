#include	"Game.h"
#include	"GameDefine.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;

/**
 * コンストラクタ
 *
 */
CGame::CGame() :
m_Texture() {
}

/**
 * デストラクタ
 *
 */
CGame::~CGame()
{
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGame::Load(void)
{
	//プレイヤー素材の読み込み
	m_Player.Load();
	//ステージ素材の読み込み
	m_Stage.Load("Stage.txt");
	if (!m_Texture.Load("HP.png"))
		return false;
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//アイテムメモリ確保
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//はてなブロックメモリ確保
	m_HatenaArray = new CHatena[m_Stage.GetHatenaCount()];
	//エフェクトの素材読み込み
	m_EffectManager.Load();

	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGame::Initialize(void)
{
	//プレイヤーの状態初期化
	m_Player.Initialize();
	//ステージの状態初期化
	m_Stage.Initialize(m_EnemyArray, m_ItemArray, m_HatenaArray);
	//エフェクトの状態初期化
	m_EffectManager.Initialize();
	//プレイヤーと敵にエフェクトクラスの設定
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}
}

/**
 * 更新
 *
 */
void CGame::Update(void)
{
	//プレイヤーの更新
	m_Player.Update();
	//ステージとプレイヤーの当たり判定
	float ox = 0, oy = 0;
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}
	//敵の更新
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		//非表示の場合
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update(m_Stage.GetScrollX(), m_Stage.GetScrollY());
		float ox = 0, oy = 0;
		//敵とステージの当たり判定
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
		//敵が下に落ちないようにする当たり判定
		if (!m_Stage.Collision(m_EnemyArray[i].GetCollisionRect(), ox, oy))
		{
			m_EnemyArray[i].SetMoveX();
		}
	}
	//アイテムの更新
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		//非表示の場合
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		//ステージとアイテムの当たり判定
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy))
		{
			m_ItemArray[i].CollisionStage(ox, oy);
		}
	}
	//各当たり判定の実行
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		//プレイヤーと敵の当たり判定
		m_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for (int i = 0; i < m_Stage.GetHatenaCount(); i++)
	{
		//アイテムの数だけ繰り返す
		for (int j = 0; j < m_Stage.GetItemCount(); j++)
		{
			//はてなブロックとプレイヤーの当たり判定
			m_HatenaArray[i].CollisionPlayer(m_Player.GetRect(), m_ItemArray[j]);
		}
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		//プレイヤーとアイテムの当たり判定
		m_Player.CollisionItem(m_ItemArray[i]);
	}
	//ステージの更新
	m_Stage.Update(m_Player);
	//エフェクトの更新
	m_EffectManager.Update();

	//プレイヤーのゴールフラグでゲームクリア画面へ
	if (m_Player.IsGoal())
	{
		gChangeScene = SCENENO_GAMECLEAR;
	}


	//F2キーでゲームクリア画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		gChangeScene = SCENENO_GAMECLEAR;
	}
	//プレイヤーの終了フラグでゲームオーバー画面へ
	if (m_Player.IsEnd())
	{
		gChangeScene = SCENENO_GAMEOVER;
	}
	//F3キーでゲームオーバー画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		gChangeScene = SCENENO_GAMEOVER;
	}
}

/**
 * 描画
 *
 */
void CGame::Render(void)
{
	//ステージの描画
	m_Stage.Render();
	//HPの描画
	for (int i = 0; i < m_Player.GetHP(); i++)
	{
		m_Texture.Render(10 + (m_Texture.GetWidth() + 5) * i, 10);
	}
	//プレイヤーの描画
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//敵の描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//アイテムの描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//はてなブロックの描画
	for (int i = 0; i < m_Stage.GetHatenaCount(); i++)
	{
		m_HatenaArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//エフェクトの描画
	m_EffectManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

/**
 * デバッグ描画
 *
 */
void CGame::RenderDebug(void)
{
	//ステージのデバッグ描画
	m_Stage.RenderDebug();
	//プレイヤーのデバッグ描画
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//敵のデバッグ描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//アイテムのデバッグ描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//エフェクトのデバッグ描画
	m_EffectManager.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

/**
 * 解放
 *
 */
void CGame::Release(void)
{
	//テクスチャの解放
	m_Texture.Release();
	//ステージの解放
	m_Stage.Release();
	//プレイヤーの解放
	m_Player.Release();
	//敵の解放
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//アイテムの解放
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//はてなブロックの解放
	if (m_HatenaArray)
	{
		delete[] m_HatenaArray;
		m_HatenaArray = NULL;
	}
	//エフェクトの解放
	m_EffectManager.Release();
}
