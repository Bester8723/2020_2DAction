#include "Player.h"

/**
 * コンストラクタ
 *
 */
CPlayer::CPlayer() :
	m_Texture(),
	m_Motion(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_bMove(false),
	m_MoveX(0.0f),
	m_MoveY(0.0f),
	m_JumpCount(0),
	m_bReverse(false),
	m_HP(0),
	m_SrcRect() {
}

/**
 * デストラクタ
 *
 */
CPlayer::~CPlayer()
{
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CPlayer::Load(void)
{
	//テクスチャの読み込み
	if (!m_Texture.Load("player.png"))
	{
		return false;
	}

	//アニメーションを作成
	SpriteAnimationCreate anim[] = {
		{
			"待機",
			0,0,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"移動",
			0,70,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
		},
		{
			"ジャンプ上昇",
			0,140,
			60,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"ジャンプ下降",
			240,140,
			60,64,
			FALSE,{{2,0,0},{2,1,0}}
		},
		{
			"ダメージ",
			480,0,
			60,64,
			FALSE,{{20,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);

	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * プレイヤーの位置など状態を初期化したいときに実行する。
 */
void CPlayer::Initialize(void)
{
	m_PosX = 20;
	m_PosY = 640 - m_Motion.GetSrcRect().GetHeight();
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_JumpCount = 0;
	m_HP = 2;
	m_DamageWait = 0;
	m_bEnd = false;
	m_pEndEffect = NULL;
	m_bGoal = false;
	m_Motion.ChangeMotion(MOTION_WAIT);
}

/**
 * 更新
 *
 */
void CPlayer::Update(void)
{
	//HPがなくなると爆発の終了を待機して終了
	if (m_HP <= 0)
	{
		if (!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bEnd = true;
		}
		return;
	}
	//移動フラグ、このフレームでの移動があったかを保存
	m_bMove = false;
	//ジャンプ下降への切り替え
	if (m_Motion.GetMotionNo() == MOTION_JUMPSTART && m_MoveY >= 0)
	{
		m_Motion.ChangeMotion(MOTION_JUMPEND);
	}
	//着地の場合の動作
	if (m_Motion.GetMotionNo() == MOTION_JUMPEND)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion() && m_MoveY == 0)
		{
			m_JumpCount = 0;
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//ダメージ中の動作
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else
	{
		//キー入力による操作
		UpdateKey();
	}
	//移動更新
	UpdateMove();
	//実際に座標を移動させる
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;
	//画面外で落下としてHPを０にする
	if (m_PosY >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION02);
	}
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//ダメージのインターバルを減らす
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

/**
 * キー入力による動作更新
 *
 */
void CPlayer::UpdateKey(void)
{
	//キーボードでの移動
	//入力で直接座標を動かすのではなく、速度を変化させる。
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_MoveX -= PLAYER_SPEED;
		m_bReverse = true;
		m_bMove = true;
		if (m_MoveX < -PLAYER_MAXSPEED)
		{
			m_MoveX = -PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_MoveX += PLAYER_SPEED;
		m_bReverse = false;
		m_bMove = true;
		if (m_MoveX > PLAYER_MAXSPEED)
		{
			m_MoveX = PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	//上キーでジャンプ
	if (g_pInput->IsKeyPush(MOFKEY_UP) && m_JumpCount < 2)
	{
		//ジャンプ回数によって速度変化
		switch (m_JumpCount)
		{
		case 0:	m_MoveY = PLAYER_JUMP;
			break;
		case 1: m_MoveY = PLAYER_JUMP * 0.8f;
			break;
		}
		m_JumpCount++;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
	}
}

/**
 * 移動更新
 *
 */
void CPlayer::UpdateMove(void)
{
	//このフレームでの移動入力がなければ減速処理を実行する
	if (!m_bMove)
	{
		if (m_MoveX > 0)
		{
			m_MoveX -= PLAYER_SPEED * 1.3f;
			if (m_MoveX <= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_MoveX < 0)
		{
			m_MoveX += PLAYER_SPEED * 1.3f;
			if (m_MoveX >= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//重力により下に少しずつ下がる
	if (!g_pInput->IsKeyHold(MOFKEY_UP))
	{
		m_MoveY += GRAVITY * 2;
	}
	else 
	{
		m_MoveY += GRAVITY;
	}
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
}

/**
 * 描画
 *
 * 引数
 * [in]					wx				ワールドの変化
 * [in]					wy				ワールドの変化
 */
void CPlayer::Render(float wx, float wy)
{
	//インターバル２　フレームごとに描画をしない
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}
	//描画矩形
	CRectangle dr = m_SrcRect;
	//描画位置
	float px = m_PosX - wx;
	float py = m_PosY - wy;
	//反転フラグが ON の場合、描画矩形を反転させる
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//テクスチャの描画
	m_Texture.Render(px, py, dr);
}

/**
 * デバッグ描画
 *
 * 引数
 * [in]					wx				ワールドの変化
 * [in]					wy				ワールドの変化
 */
void CPlayer::RenderDebug(float wx, float wy)
{
	//位置の描画
	CGraphicsUtilities::RenderString(10, 70, "プレイヤー位置 X : %.0f , Y : %.0f", m_PosX, m_PosY);
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	//はてなブロックとの当たり判定
	hr.Bottom = hr.Top + 1;
	hr.Top -= 2;
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 255));
}

/**
 * 解放
 *
 */
void CPlayer::Release(void)
{
	m_Texture.Release();
	m_Motion.Release();
}

/**
 * ステージとの当たり
 *
 * 引数
 * [in]				ox				Ｘ埋まり量
 * [in]				oy				Ｙ埋まり量
 */
void CPlayer::CollisionStage(float ox, float oy)
{
	//埋まった分を戻す
	m_PosX += ox;
	m_PosY += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
		if (m_JumpCount != 0)
		{
			m_JumpCount = 0;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

/**
 * 当たり判定
 * 引数の敵に対して矩形同士の当たり判定を実行する。
 * 当たっていた場合はプレイヤーの状態を変更する。
 *
 * 引数
 * [in]				ene				判定を行う敵
 *
 * 戻り値
 * 当たっている場合はtrue、当たっていなければfalseを返す
 */
bool CPlayer::CollisionEnemy(CEnemy& ene)
{
	if (!ene.GetShow())
	{
		return false;
	}
	//HPがなくなると当たり判定しない
	if (m_HP <= 0)
	{
		return false;
	}
	//ダメージ中のため、当たり判定を行わない
	if (m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}
	//敵の矩形と自分の矩形でダメージ
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();
	if (prec.CollisionRect(erec))
	{
		//踏みつけ時は敵にダメージ
		if (m_MoveY > 0)
		{
			ene.Damage(10, m_bReverse);
		}
		else
		{
			m_HP--;
			m_DamageWait = 60;
			if (prec.Left < erec.Left)
			{
				m_MoveX = -5.0f;
				m_bReverse = false;
			}
			else
			{
				m_MoveX = 5.0f;
				m_bReverse = true;
			}
			m_Motion.ChangeMotion(MOTION_DAMAGE);
			if (m_HP <= 0)
			{
				//爆発エフェクトを発生させる
				m_pEndEffect = m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION02);
			}
			else
			{
				//ダメージエフェクトを発生させる
				m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_DAMAGE);
			}
		}

		return true;
	}

	return false;
}

/**
* 当たり判定
* 引数のアイテムに対して矩形同士の当たり判定を実行する。
* 当たっていた場合はプレイヤーの状態を変更する。
*
* 引数
* [in]				itm				判定を行うアイテム
*
* 戻り値
* 当たっている場合はtrue、当たっていなければfalseを返す
*/
bool CPlayer::CollisionItem(CItem & itm)
{
	if (!itm.GetShow() || !itm.GetCollision())
	{
		return false;
	}
	//アイテムの矩形と自分の矩形で当たり判定
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	//アイテムのタイプがゴールである場合、当たり判定を狭める
	if (itm.GetType() == ITEM_GOAL)
	{
		irec.Right -= 5;
		irec.Left += 5;
	}
	//プレイヤーとアイテムの当たり
	if (prec.CollisionRect(irec))
	{
		//アイテムを非表示にする
		itm.SetShow(false);
		//アイテムのタイプによって効果を変える
		switch (itm.GetType())
		{
		case ITEM_RECOVER:
			m_HP++;
			break;
		case ITEM_GOAL:
			m_bGoal = true;
			break;
		}
		return true;
	}
	return false;
}
