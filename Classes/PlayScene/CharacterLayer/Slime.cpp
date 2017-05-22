/// <summary>
/// �T�@�v�F�X���C���N���X�̒�`
/// �쐬�ҁFGS2 24 �R�{�I��
/// �쐬���F2017/05/15
/// </summary>

/* ---- ���C�u�����̃C���N���[�h ---------- */

#include "Slime.h"

/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;
using namespace cocos2d::experimental;
bool Slime::init()
{
	if (!Character::init())
	{

		return false;
	}

	GameManager::ScoreCorrection = 1.1f;
	// ���ʂ̉摜����ύX
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Images/slime_chara.png");

	s_player->setTexture(texture);
	s_player->setContentSize(texture->getContentSize());

	JumpSize = 11.0f;

	return true;
}
