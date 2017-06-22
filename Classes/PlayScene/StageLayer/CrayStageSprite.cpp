/***************************************************************************
*|
*|	�T�v�@�R�C���N���X�̒�`
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ----  �C���N���[�h ---------- */
#include "CrayStageSprite.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace std;
/***************************************************************************
*|	�T�v�@�@����������
*|	�����@�@�摜���A���E���_�̍��W
*|�@�߂�l�@���N���X�̏���������������������
****************************************************************************/
bool CrayStageSprite::init(std::string filename)
{
	if (!Sprite::initWithFile(filename)) {

		return false;
	}
	//������
	m_size = MAX_SIZE;

	m_flame_cnt = 0;
	m_time = 0;
	// Register Touch Event
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();

	//listener->onTouchesBegan = CC_CALLBACK_2(CrayStageSprite::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(CrayStageSprite::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(CrayStageSprite::onTouchesEnded, this);
	//listener->onTouchesCancelled = CC_CALLBACK_2(CrayStageSprite::onTouchesCancelled, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//_touchListener = listener;
	hit_flag = true;

	//���t���[���Ă�
	this->scheduleUpdate();

	return true;
}


/***************************************************************************
*|	�T�v�@�@�X�v���C�g���쐬����B
*|	�����@	�摜���A���E�̍��W���_
*|�@�߂�l�@�V�[���̃A�h���X
****************************************************************************/
CrayStageSprite* CrayStageSprite::create(string filename)
{
	//�������m��
	CrayStageSprite *pRet = new(nothrow)CrayStageSprite();

	if (pRet && pRet->init(filename))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

}





void CrayStageSprite::update(float data)
{
	this->setScale(m_size.x / MAX_SIZE.x, m_size.y / MAX_SIZE.y);

	//�m�[���͂��̏����𖳎�����
	if (GameManager::Mold != GameManager::Gnome) {
		//�v���C���[�ƔS�y���̏Փ˔���
		CollisionPlayer();
	}

	//
	//if (m_leap_flag) {
	//	
	//	if (m_size.y < 32)
	//	{
	//		m_leap_flag = false;
	//	}
	//	m_size.y -= 10;
	//}
	//�Q�[�����n�܂��Ă���̃t���[����
	//m_flame_cnt++;
}



/***************************************************************************
*|	�T�v�@	�v���C���[�ƔS�y���̏Փ˔���
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CrayStageSprite::CollisionPlayer()
{
	
	switch (GameManager::CollisionDetermination
	(Vec2(this->getPosition().x, this->getPosition().y +  m_size.y), (m_size),
		GameManager::PlayerPos, GameManager::PlayerSize))
	{
	case GameManager::right:
		//GameManager::PlayerPos.x = this->getPosition().x /*+ MAX_SIZE.x - m_size.x / 2*/ - GameManager::PlayerSize.x / 2;
		//GameManager::PlayerSpd.x = 0.0f;
		break;
	case GameManager::left:
		
		
			GameManager::GameOverFlag = true;
		

		////���������̂Œׂ��
		//character->s_player->setAnchorPoint(Vec2(0, 0));
		//GameManager::PlayerSize.x = 32;
		//GameManager::PlayerPos.x += 96;
		break;
	case GameManager::up:
		if (!GameManager::JumpState)
		{
			GameManager::PlayerPos.y = this->getPosition().y + m_size.y;
			GameManager::PlayerSpd.y = 0.0f;
			//�W�����v�\�ɂ���
			GameManager::JumpCnt = 0;
			GameManager::JumpFlag = true;
		}

		break;
	case GameManager::under:
		
			GameManager::PlayerPos.y = this->getPosition().y/* - MAX_SIZE.y*/ - GameManager::PlayerSize.y - 2;
			GameManager::PlayerSpd.y = 0.0f;		
		break;
	default:
		break;

	}

	
}

/***************************************************************************
*|	�T�v�@	�X���C�v���ꂽ�Ƃ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CrayStageSprite::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	log("onTouchesMoved");

	//�^�b�`ID�i�[
	int g_touch_id;

	//�^�b�`�̐��������[�v
	for (auto &item : touches)
	{
		//�^�b�`��ID���擾����
		auto touch = item;
		//�^�b�`ID�擾
		g_touch_id = touch->getID();

		//3�ڈȏ�̃^�b�`�͎󂯕t���Ȃ�
		if (g_touch_id < EFFECTIVENESSTOUCH)
		{
			//���W���擾����
			touchpos[g_touch_id] = touch->getLocation();
			touchpos[g_touch_id].x += GameManager::m_cameraposx - 480;
		}
	}


	//���ȏ�^�b�`���ꂽ��
	if (g_touch_id >= 1)
	{
		MultiTouchCrayStage();
		
	}



}

/***************************************************************************
*|	�T�v	�����ꂽ�Ƃ�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CrayStageSprite::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	////����������
	//for (int i = 0; i < EFFECTIVENESSTOUCH; i++)
	//{
	//	touchpos[i] = Vec2(0.0f, 0.0f);
	//	old_touchpos[i] = Vec2(0.0f, 0.0f);
	//}

}




/***************************************************************************
*|	�T�v	��̎w���������Ă��邩���߂�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CrayStageSprite::MultiTouchCrayStage()
{
	log("######   multi");
	//�L���ȃ^�b�`�̐�
	const int EFFECTIVENESSTOUCH = 2;

	//�^�b�`���L�����N�^�[�ɓ���������
	bool m_touch_collision[EFFECTIVENESSTOUCH];

	//�^�b�`���v���C���[�ɓ���������
	m_touch_collision[0] = GameManager::HitJudgment(
		touchpos[GameManager::First]/* - Vec2(GameManager::TOUCH_SIZE.x / 2, -GameManager::TOUCH_SIZE.y / 2)*/,Vec2(0.0f,0.0f)/* GameManager::TOUCH_SIZE*/,
		getPosition() + Vec2(m_size.x, 0), m_size);

	//�^�b�`2���v���C���[�ɓ���������
	m_touch_collision[1] = GameManager::HitJudgment(
		touchpos[GameManager::Second] /*- Vec2(GameManager::TOUCH_SIZE.x / 2, -GameManager::TOUCH_SIZE.y / 2)*/, Vec2(0.0f, 0.0f),
		getPosition() + Vec2(m_size.x, 0), m_size);



	//�^�b�`����Ƃ�����������
	if (m_touch_collision[0] == true && m_touch_collision[1] == true)
	{
		m_size.y= 32;
		DirectionJudgment();
	}
}



/***************************************************************************
*|	�T�v	�㉺�����E�ǂ���ɏ������Ȃ邩���߂�
*|	�����@�@����
*|�@�߂�l�@����
****************************************************************************/
void CrayStageSprite::DirectionJudgment()
{

	//�O�t���[�������̊֐���ʂ�����
	//if (!hit_flag)
	//{
	//	float DistanceX[EFFECTIVENESSTOUCH];
	//	float total_distanceX = 0;
	//	for (int i = 0; i < EFFECTIVENESSTOUCH; i++)
	//	{
	//		//���E�ɂǂꂾ����������
	//		DistanceX[i] = abs(old_touchpos[i].x - touchpos[i].x);
	//		total_distanceX += DistanceX[i];
	//	}

	//	float DistanceY[EFFECTIVENESSTOUCH];
	//	float total_distanceY = 0;
	//	for (int i = 0; i < EFFECTIVENESSTOUCH; i++)
	//	{
	//		//�㉺�ɂǂꂾ����������
	//		DistanceY[i] = abs(old_touchpos[i].y - touchpos[i].y);
	//		total_distanceY += DistanceY[i];
	//	}

		//�v���C�������E�㉺�ǂ���ɋ������Ƃ�����
		//���E�Ȃ�
		//if (total_distanceX >= total_distanceY)
		{
			//m_size.x -= total_distanceX;

			/*m_size.y = 32;*/
			
		}
	/*	m_leap_flag = true;
		m_time = m_flame_cnt;
		hit_flag = true;*/
		/*	else
		{

				m_size.y -= total_distanceY;

		}
*/
//�X�V����
	/*	old_touchpos[GameManager::First] = touchpos[GameManager::First];
		old_touchpos[GameManager::Second] = touchpos[GameManager::Second];*/
		//}
		//�O�t���[���ʂ��ĂȂ��Ƃ�
		//else
		//{
		//	//�X�V����
		//	old_touchpos[GameManager::First] = touchpos[GameManager::First];
		//	old_touchpos[GameManager::Second] = touchpos[GameManager::Second];
			//hit_flag = true;
		//}
	//}
}





