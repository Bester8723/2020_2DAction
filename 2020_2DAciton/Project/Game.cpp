#include	"Game.h"
#include	"GameDefine.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;

/**
 * �R���X�g���N�^
 *
 */
CGame::CGame() :
m_Texture() {
}

/**
 * �f�X�g���N�^
 *
 */
CGame::~CGame()
{
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGame::Load(void)
{
	//�v���C���[�f�ނ̓ǂݍ���
	m_Player.Load();
	//�X�e�[�W�f�ނ̓ǂݍ���
	m_Stage.Load("Stage.txt");
	if (!m_Texture.Load("HP.png"))
		return false;
	//�G�������m��
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//�A�C�e���������m��
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//�͂Ăȃu���b�N�������m��
	m_HatenaArray = new CHatena[m_Stage.GetHatenaCount()];
	//�G�t�F�N�g�̑f�ޓǂݍ���
	m_EffectManager.Load();

	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGame::Initialize(void)
{
	//�v���C���[�̏�ԏ�����
	m_Player.Initialize();
	//�X�e�[�W�̏�ԏ�����
	m_Stage.Initialize(m_EnemyArray, m_ItemArray, m_HatenaArray);
	//�G�t�F�N�g�̏�ԏ�����
	m_EffectManager.Initialize();
	//�v���C���[�ƓG�ɃG�t�F�N�g�N���X�̐ݒ�
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}
}

/**
 * �X�V
 *
 */
void CGame::Update(void)
{
	//�v���C���[�̍X�V
	m_Player.Update();
	//�X�e�[�W�ƃv���C���[�̓����蔻��
	float ox = 0, oy = 0;
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}
	//�G�̍X�V
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		//��\���̏ꍇ
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update(m_Stage.GetScrollX(), m_Stage.GetScrollY());
		float ox = 0, oy = 0;
		//�G�ƃX�e�[�W�̓����蔻��
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
		//�G�����ɗ����Ȃ��悤�ɂ��铖���蔻��
		if (!m_Stage.Collision(m_EnemyArray[i].GetCollisionRect(), ox, oy))
		{
			m_EnemyArray[i].SetMoveX();
		}
	}
	//�A�C�e���̍X�V
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		//��\���̏ꍇ
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		//�X�e�[�W�ƃA�C�e���̓����蔻��
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy))
		{
			m_ItemArray[i].CollisionStage(ox, oy);
		}
	}
	//�e�����蔻��̎��s
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		//�v���C���[�ƓG�̓����蔻��
		m_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for (int i = 0; i < m_Stage.GetHatenaCount(); i++)
	{
		//�A�C�e���̐������J��Ԃ�
		for (int j = 0; j < m_Stage.GetItemCount(); j++)
		{
			//�͂Ăȃu���b�N�ƃv���C���[�̓����蔻��
			m_HatenaArray[i].CollisionPlayer(m_Player.GetRect(), m_ItemArray[j]);
		}
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		//�v���C���[�ƃA�C�e���̓����蔻��
		m_Player.CollisionItem(m_ItemArray[i]);
	}
	//�X�e�[�W�̍X�V
	m_Stage.Update(m_Player);
	//�G�t�F�N�g�̍X�V
	m_EffectManager.Update();

	//�v���C���[�̃S�[���t���O�ŃQ�[���N���A��ʂ�
	if (m_Player.IsGoal())
	{
		gChangeScene = SCENENO_GAMECLEAR;
	}


	//F2�L�[�ŃQ�[���N���A��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		gChangeScene = SCENENO_GAMECLEAR;
	}
	//�v���C���[�̏I���t���O�ŃQ�[���I�[�o�[��ʂ�
	if (m_Player.IsEnd())
	{
		gChangeScene = SCENENO_GAMEOVER;
	}
	//F3�L�[�ŃQ�[���I�[�o�[��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		gChangeScene = SCENENO_GAMEOVER;
	}
}

/**
 * �`��
 *
 */
void CGame::Render(void)
{
	//�X�e�[�W�̕`��
	m_Stage.Render();
	//HP�̕`��
	for (int i = 0; i < m_Player.GetHP(); i++)
	{
		m_Texture.Render(10 + (m_Texture.GetWidth() + 5) * i, 10);
	}
	//�v���C���[�̕`��
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//�G�̕`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�A�C�e���̕`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�͂Ăȃu���b�N�̕`��
	for (int i = 0; i < m_Stage.GetHatenaCount(); i++)
	{
		m_HatenaArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�G�t�F�N�g�̕`��
	m_EffectManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

/**
 * �f�o�b�O�`��
 *
 */
void CGame::RenderDebug(void)
{
	//�X�e�[�W�̃f�o�b�O�`��
	m_Stage.RenderDebug();
	//�v���C���[�̃f�o�b�O�`��
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//�G�̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�A�C�e���̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�G�t�F�N�g�̃f�o�b�O�`��
	m_EffectManager.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

/**
 * ���
 *
 */
void CGame::Release(void)
{
	//�e�N�X�`���̉��
	m_Texture.Release();
	//�X�e�[�W�̉��
	m_Stage.Release();
	//�v���C���[�̉��
	m_Player.Release();
	//�G�̉��
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//�A�C�e���̉��
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//�͂Ăȃu���b�N�̉��
	if (m_HatenaArray)
	{
		delete[] m_HatenaArray;
		m_HatenaArray = NULL;
	}
	//�G�t�F�N�g�̉��
	m_EffectManager.Release();
}
