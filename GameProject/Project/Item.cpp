#include	"Item.h"

/**
 * コンストラクタ
 *
 */
CItem::CItem() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bShow(false) ,
m_SrcRect() ,
m_bCollision(false) {
}

/**
 * デストラクタ
 *
 */
CItem::~CItem(){
	//delete[] で解放されるようにReleaseをデストラクタで実行する
	Release();
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 *
 * 引数
 * [in]			px					X座標
 * [in]			py					Y座標
 * [in]			type				アイテムタイプ
 */
void CItem::Initialize(float px,float py,int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.3f;
	m_MoveY = 0.0f;
	m_bShow = true;
	if (!GetType() == ITEM_GOAL)
	{
		m_bCollision = false;
	}
	else
	{
		m_bCollision = true;
		m_MoveX = 0.0f;
	}
	//アニメーションを作成
	SpriteAnimationCreate anim[] = {
		{
			"アイテム",
			0,0,
			32,32,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"ゴール",
			0,0,
			32,320,
			TRUE,{{30,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
	//アニメーションの初期設定
	if (GetType() == ITEM_RECOVER)
	{
		m_Motion.ChangeMotion(MOTION_MOVE);
	}
	else if (GetType() == ITEM_GOAL)
	{
		m_Motion.ChangeMotion(MOTION_GOAL);
	}
}

/**
 * 更新
 *
 */
void CItem::Update(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//はてなブロックからドロップしたら動く
	if (m_bCollision)
	{
		//重力により下に少しずつ下がる
		m_MoveY += GRAVITY * 0.7;
		if (m_MoveY >= 20.0f)
		{
			m_MoveY = 20.0f;
		}
		//実際に座標を移動させる
		m_PosX += m_MoveX;
		m_PosY += m_MoveY;
	}
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

/**
 * ステージとの当たり
 *
 * 引数
 * [in]			ox					X埋まり量
 * [in]			oy					Y埋まり量
 */
void CItem::CollisionStage(float ox,float oy){
	//はてなブロックに埋まってるとき
	if (!m_bCollision)
	{
		return;
	}
	m_PosX += ox;
	m_PosY += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if(oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if(oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if(ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
	}
	else if(ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

/**
 * 描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CItem::Render(float wx,float wy){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX - wx,m_PosY - wy,m_SrcRect);
}

/**
 * デバッグ描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CItem::RenderDebug(float wx,float wy){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx,hr.Top - wy,hr.Right - wx,hr.Bottom - wy,MOF_XRGB(255,0,0));
}

/**
 * 解放
 *
 */
void CItem::Release(void){
	m_Motion.Release();
}

/**
 * アイテム出現
 *
 */
void CItem::Drop()
{
	m_bCollision = true;
	m_PosY -= m_SrcRect.GetHeight();
}
