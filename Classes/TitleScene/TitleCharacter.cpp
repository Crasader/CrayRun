/// �쐬�ҁFGS2 16 ���c�N��
/// �쐬���F2017/05/26
/// </summary>
#include "TitleCharacter.h"
/* ---- ���O��Ԃ���� -------------------- */
USING_NS_CC;


bool TitleChracter::init()
{	
	//�m�[�h�̍쐬�Ɏ��s������false��Ԃ�
	if (!Node::init())
	{
		return false;
	}

	//�^�C�g���L�����N�^
	title_character = Sprite::create("Images/Player2.png");
	title_character->setPosition(Vec2(-100.0f,250));
	this->addChild(title_character);


	//���ɑ��葱����̂����s�[�g
	MoveBy* action00 = MoveBy::create(2.5, Vec2(270, 0.0f));

	JumpBy* action1 = JumpBy::create(1, Vec2(300.0f, 0.0f),130, 1);
	CallFunc* audioaction = CallFunc::create(CC_CALLBACK_0(TitleChracter::PlayJumpAudio, this));
	Spawn* JumpSpan = Spawn::create(action1, audioaction, nullptr);

	MoveTo* action2 = MoveTo::create(0.0f, Vec2(-100.0f, 250.0f));
	Sequence* action3 = Sequence::create(action00, JumpSpan, JumpSpan, action00, action2, nullptr);
	RepeatForever* action4 = RepeatForever::create(action3);
	title_character->runAction(action4);


	walkCnt = 0;

	this->scheduleUpdate();

	return true;
}

void TitleChracter::update(float data)
{
	walkCnt++;
	Animation();
}




void TitleChracter::Animation()
{
	Texture2D* texture;

		switch (walkCnt / 5 % 4)
		{
		case 0:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Player2.png");

			title_character->setTexture(texture);
			title_character->setContentSize(texture->getContentSize());

			break;
		case 1:
		case 3:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Player_w.png");

			title_character->setTexture(texture);
			title_character->setContentSize(texture->getContentSize());

			break;
		case 2:
			texture = TextureCache::sharedTextureCache()->addImage("Images/Player_w2.png");

			title_character->setTexture(texture);
			title_character->setContentSize(texture->getContentSize());

			break;
		}
	}