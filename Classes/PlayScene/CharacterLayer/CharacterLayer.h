/***************************************************************************
*|
*|	�T�v�@�@�L�����N�^�[���C���[�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/4/20
*|___________________________________________________________________________
****************************************************************************/
/* ---- ���d�C���N���[�h�̖h�~ ---------- */
#pragma once 
/* ----  �C���N���[�h ---------- */
#include "cocos2d.h"
#include "../../GameManager.h"
#include "Character.h"
#include "Rabbit.h"
#include "Slime.h"
#include "Gnome.h"
#include "Phoenix.h"
#include "Witch.h"
#include "audio/include/AudioEngine.h"

//�L���ȃ^�b�`�̐�
 const int EFFECTIVENESS_TOUCH = 2;
class CharacterLayer :public cocos2d::Layer
{

public:
	virtual bool init();

	CREATE_FUNC(CharacterLayer);
	//�L�����N�^�[�I�u�W�F�N�g
	Character* character;



private:


	//���t���[���Ăяo�����֐�
	void update(float delta)override;
	//�^�b�`���ɌĂяo�����
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�X���C�v���ɌĂяo�����
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�^�b�`�������ꂽ
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//�^�b�`�ُ�I��
	void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);

	//�L�����N�^�[�̃}���`�^�b�`����
	void  MultiTouchCharacter();


	//���^�̕ύX
	void ChangeMold();
	//�v���C���[�ƃX�e�[�W�̂����蔻��
	void CollisionResponseFloor();
	//�W�����v���邩���ׂ�
	void JumpInvestigate();

	//�^�b�`ID�i�[
	int m_touch_id;
	
	//�^�b�`���W
	cocos2d::Vec2 touchpos[EFFECTIVENESS_TOUCH];

	//�^�b�`�T�C�Y
	const cocos2d::Vec2 TOUCH_SIZE = cocos2d::Vec2(96,96);
	int FirstTouchCnt;//�ŏ��̃^�b�`����ǂꂾ���o�߂�����
	bool FirstTouchFlag = false;//�ŏ��̃^�b�`���Ă΂ꂽ��

	//�ŏ��̍��W
	cocos2d::Vec2 FirstPos[EFFECTIVENESS_TOUCH];
	

	int FirstMultiTouchFlag;


	//�O��̃L�����N�^�^�C�v
	GameManager::CharacterKind old_chara_kind;


	//�L�����N�^�̃{�C�X
	int m_character_voice[GameManager::MaxCharacterKind];
	//���܂��{�C�X
	int m_SandWicheSE;

	//���܂��{�C�X�Đ�
	void PlaySandWicheSE() {
		if (m_SandWicheSE == 0)
		{
			m_SandWicheSE = cocos2d::experimental::AudioEngine::play2d("Sounds/Interpose.mp3");
		}
	}
	//�L�����N�^�{�C�X��S�Ď~�߂�֐�
	void CharacterVoiceStop();
};

