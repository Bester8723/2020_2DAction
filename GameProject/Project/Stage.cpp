#include	"Stage.h"
#include	<sys/stat.h>

/**
 * コンストラクタ
 *
 */
CStage::CStage() :
	m_ChipTexture(),
	m_BackTexture(),
	m_ChipSize(0),
	m_XCount(0),
	m_YCount(0),
	m_pChipData(NULL),
	m_ScrollX(0),
	m_ScrollY(0),
	m_EnemyTextureCount(0),
	m_pEnemyTexture(NULL),
	m_EnemyCount(0),
	m_ItemTextureCount(0),
	m_pItemTexture(NULL),
	m_ItemCount(0),
	m_HatenaTextureCount(0),
	m_pHatenaTexture(NULL),
	m_HatenaCount(0) {
}

/**
 * デストラクタ
 *
 */
CStage::~CStage() {
}

/**
 * 読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			pName				ステージファイルの名前
 */
bool CStage::Load(char* pName) {
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
	if (!LoadMap(pstr))
		return false;
	//敵の読み込み
	pstr = strtok(NULL, ",");
	if (!LoadEnemy(pstr))
		return false;
	//アイテムの読み込み
	pstr = strtok(NULL, ",");
	if (!LoadItem(pstr))
		return false;
	//はてなブロックの読み込み
	pstr = strtok(NULL, ",");
	if (!LoadHatena(pstr))
		return false;

	//ファイルを閉じる
	fclose(fp);
	free(pBuffer);

	return true;
}

/**
 * マップの読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			pMapStr				利用する文字列
 */
bool CStage::LoadMap(char* pMapStr)
{
	//テクスチャの読み込み
	if (!m_BackTexture.Load(pMapStr))
	{
		return false;
	}
	pMapStr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pMapStr))
	{
		return false;
	}

	//チップサイズ
	m_ChipSize = atof(strtok(NULL, ","));

	//マップのチップ数
	m_XCount = atoi(strtok(NULL, ","));
	m_YCount = atoi(strtok(NULL, ","));

	//マップチップ用のメモリを確保
	m_pChipData = (char*)malloc(m_XCount * m_YCount);

	//チップデータの読み込み
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pChipData[y * m_XCount + x] = atoi(strtok(NULL, ","));
		}
	}

	return true;
}

/**
 * 敵の読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			pEnemyStr				利用する文字列
 */
bool CStage::LoadEnemy(char* pEnemyStr)
{
	//敵のテクスチャの読み込み
	m_EnemyTextureCount = atoi(pEnemyStr);
	m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
	for (int i = 0; i < m_EnemyTextureCount; i++)
	{
		pEnemyStr = strtok(NULL, ",");
		if (!m_pEnemyTexture[i].Load(pEnemyStr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pEnemyData = (char*)malloc(m_XCount * m_YCount);
	m_EnemyCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pEnemyData[y * m_XCount + x] = atoi(strtok(NULL, ","));
			if (m_pEnemyData[y * m_XCount + x] > 0)
			{
				m_EnemyCount++;
			}
		}
	}

	return true;
}

/**
 * アイテムの読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			pItemStr				利用する文字列
 */
bool CStage::LoadItem(char* pItemStr)
{
	//アイテムのテクスチャ読み込み
	m_ItemTextureCount = atoi(pItemStr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for (int i = 0; i < m_ItemTextureCount; i++)
	{
		pItemStr = strtok(NULL, ",");
		if (!m_pItemTexture[i].Load(pItemStr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pItemData = (char*)malloc(m_XCount * m_YCount);
	m_ItemCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pItemStr = strtok(NULL, ",");
			m_pItemData[y * m_XCount + x] = atoi(pItemStr);
			if (m_pItemData[y * m_XCount + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}

	return true;
}

/**
 * はてなブロックの読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			phatenaStr				利用する文字列
 */
bool CStage::LoadHatena(char* pHatenaStr)
{
	//はてなブロックのテクスチャ読み込み
	m_HatenaTextureCount = atoi(pHatenaStr);
	m_pHatenaTexture = new CTexture[m_HatenaTextureCount];
	for (int i = 0; i < m_HatenaTextureCount; i++)
	{
		pHatenaStr = strtok(NULL, ",");
		if (!m_pHatenaTexture[i].Load(pHatenaStr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pHatenaData = (char*)malloc(m_XCount * m_YCount);
	m_HatenaCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pHatenaStr = strtok(NULL, ",");
			m_pHatenaData[y * m_XCount + x] = atoi(pHatenaStr);
			if (m_pHatenaData[y * m_XCount + x] > 0)
			{
				m_HatenaCount++;
			}
		}
	}

	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 */
void CStage::Initialize(CEnemy* pEnemy, CItem* pItem, CHatena* pHatena) {
	m_ScrollX = 0;
	m_ScrollY = 0;

	//敵の初期化
	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号０は配置しない
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on]);
			pEnemy[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
	//アイテムの初期化
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号０は配置しない
			char on = m_pItemData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pItem[n].SetTexture(&m_pItemTexture[on]);
			pItem[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
	//はてなブロックの初期化
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号０は配置しない
			char on = m_pHatenaData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pHatena[n].SetTexture(&m_pHatenaTexture[on]);
			pHatena[n++].Initialize(x * m_ChipSize, y * m_ChipSize);
		}
	}
}

/**
 * 更新
 *
 * 引数
 * [in]				pl					プレイヤー、スクロールの判定に使用
 */
void CStage::Update(CPlayer& pl) {
	//プレイヤーの矩形を取得
	CRectangle prec = pl.GetRect();
	//スクリーンの幅
	float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	//ステージ全体の幅
	float stgw = m_ChipSize * m_XCount;
	//座標が画面端によっている（各端から400pixel）場合、スクロールを行って補正する
	if (prec.Left - m_ScrollX < 400)
	{
		m_ScrollX -= 400 - (prec.Left - m_ScrollX);
		if (m_ScrollX <= 0)
		{
			m_ScrollX = 0;
		}
	}
	else if (prec.Right - m_ScrollX > sw - 400)
	{
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - 400);
		if (m_ScrollX >= stgw - sw)
		{
			m_ScrollX = stgw - sw;
		}
	}
}

/**
 * 描画
 *
 */
void CStage::Render(void) {
	//遠景の描画
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-m_ScrollY % hn) - hn; y < sch; y += hn)
	{
		for (float x = ((int)-m_ScrollX % wn) - wn; x < scw; x += wn)
		{
			m_BackTexture.Render(x, y);
		}
	}

	//テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	//マップチップの描画
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//描画するチップ番号
			//チップ番号０は描画しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize * (cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//マップチップの描画
			m_ChipTexture.Render(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize, cr);
		}
	}
}

/**
 * デバッグ描画
 *
 */
void CStage::RenderDebug(void) {
	//位置の描画
	CGraphicsUtilities::RenderString(10, 100, "スクロール X : %.0f , Y : %.0f", m_ScrollX, m_ScrollY);
}

/**
 * 解放
 *
 */
void CStage::Release(void) {
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
	if (m_pEnemyData)
	{
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pEnemyTexture)
	{
		delete[] m_pEnemyTexture;
		m_pEnemyTexture = NULL;
	}
	if (m_pItemData)
	{
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pItemTexture)
	{
		delete[] m_pItemTexture;
		m_pItemTexture = NULL;
	}
	if (m_pHatenaData)
	{
		free(m_pHatenaData);
		m_pHatenaData = NULL;
	}
	if (m_pHatenaTexture)
	{
		delete[] m_pHatenaTexture;
		m_pHatenaTexture = NULL;
	}
}

/**
 * 当たり判定
 *
 * 引数
 * [in]			r			判定矩形
 * [out]		ox			Ｘ埋まり
 * [out]		oy			Ｙ埋まり
 */
bool CStage::Collision(CRectangle r, float& ox, float& oy)
{
	bool re = false;

	//当たり判定する矩形の左上と右下のチップ位置を求める
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;
	//ステージの範囲外にはならないようにする
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	//当たり判定をする矩形の左上から右下の範囲のみ当たり判定をおこなう
	//それ以外の番号は当たることはないので、判定が必要ない
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			//チップ番号０は当たり判定しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//当たり判定用のキャラクタ矩形
			//下で範囲を限定した専用の矩形を作成する。
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;		//下の矩形は上側を下と同じ値にする
			brec.Expansion(-6, 0);				//横の範囲を少し狭める
			//下と当たり判定
			if (cr.CollisionRect(brec))
			{
				re = true;
				//下の埋まりなので、チップ上端から矩形の下端の値を引いた値が埋まりの値
				oy += cr.Top - brec.Bottom;
				r.Top += cr.Top - brec.Bottom;
				r.Bottom += cr.Top - brec.Bottom;
			}

			//当たり判定用のキャラクタ矩形
			//左、右それぞれで範囲を限定した専用の矩形を作成する。
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;		//左の矩形は右側を左と同じ値にする
			lrec.Expansion(0, -6);				//縦の範囲を少し狭める
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;		//右の矩形は左側を右と同じ値にする
			rrec.Expansion(0, -6);				//縦の範囲を少し狭める
			//左と当たり判定
			if (cr.CollisionRect(lrec))
			{
				re = true;
				//左の埋まりなので、チップ右端から矩形の左端の値を引いた値が埋まりの値
				ox += cr.Right - lrec.Left;
				r.Left += cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//右と当たり判定
			else if (cr.CollisionRect(rrec))
			{
				re = true;
				//右の埋まりなので、チップ左端から矩形の右側の値を引いた値が埋まりの値
				ox += cr.Left - rrec.Right;
				r.Left += cr.Left - rrec.Right;
				r.Right += cr.Left - rrec.Right;
			}
			//当たり判定用のキャラクタ矩形
			//上で範囲を限定した専用の矩形を作成する。
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;		//上の矩形は下側を上と同じ値にする
			trec.Expansion(-6, 0);				//横の範囲を少し狭める
			//上と当たり判定
			if (cr.CollisionRect(trec))
			{
				re = true;
				//上の埋まりなので、チップ下端から矩形の上端の値を引いた値が埋まりの値
				oy += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}
		}
	}

	return re;
}
