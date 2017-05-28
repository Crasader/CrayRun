/***************************************************************************
*|
*|	�T�v�@�@���U���g�X�R�A�N���X�̐錾
*|�@�쐬�ҁ@GS2 16 ���c�N��
*|�@�쐬���@2017/5/10
*|___________________________________________________________________________
****************************************************************************/
#pragma once
/* ---- ���C�u�����̃C���N���[�h ---------- */
#include "cocos2d.h"
#include "../GameManager.h"
#include "audio/include/AudioEngine.h"
/* ---- �񋓌^ ---------- */
enum ScoreNumber
{
	First,
	Scound,
	Third,
	Fourth,
	Fifth,
	score
};


//�����L���O��
const int MAX_SCORE = 7;
class ResultScore :public cocos2d::Node
{
public:
	virtual bool init();
	CREATE_FUNC(ResultScore);

	//�X�R�A���擾����
	void ScoreAcquisition();
	//�X�R�A�̃����L���O�𒲂ׂ�
	void RankingSort();
	//�X�R�A�̕ۑ�
	void ScoreResister();
	//�����L���O�ɓ�������
	bool RankingInFlag;

	//�����L���O�X�R�A
	int RankingScore[6];
	//�X�R�A�̐ݒ�A�`��
	void ScoreIndicate(int Score);
	//����̃X�R�A
	static int m_Score;
	//����̋���
	static int m_distance;
	//����̕`��
	void ScoreIndicate2(int Score);
	//���ڂ̍���̐���
	int now_number;
	int ScoreMaxDigit;//�ő包��
	//����̃X�R�A�̃A�N�V����
	void ScoreAction(int cnt);
	//����̃X�R�A�̃A�N�V����
	void ResultOutAction();
	//�\�����邽�߂Ƀ����L���O�̖��O��������
	void RankingNameSubstitution();
	
	//����̃X�R�A�̃A�N�V����
	void RankingAction(int cnt);
	//�����L���O�t���O
	bool RankingFlag;
	//�����L���O�t���O
	bool RankingOutoFlag;
	//����̐����X�v���C��
	cocos2d::Sprite* s_now_number;
	//�����X�v���C�g���Ԃ牺����m�[�h
	cocos2d::Node* now_node_number[3];
	//�����X�v���C�g���Ԃ牺����m�[�h
	cocos2d::Node* node_number[MAX_SCORE + 1];
	//�^�C�g���V�[���t���O
	bool TitleFlag;
	//�A�N�V�����̑��x
	float ActionSpd;
	//���񃉃��L���O�C�������v���C���[��
	static std::string Now_Player_Name;
	//����̃X�R�A����ʊO����ł����̃t���O
	bool NowScoreOutFlag;
private:
	//����̃X�R�A����ʊO����o�����̃t���O
	void NowScoreOutFlagChnge() { NowScoreOutFlag = true; }

	void RankingFlagChange() { RankingOutoFlag = true; }

	cocos2d::UserDefault* userDefault;



	//�����X�v���C�g
	cocos2d::Sprite* s_Number;

	int SaveScore;//�X�R�A��ۑ�����
	int SaveScore2;
	int Digit;//����
	int SpriteCnt;//���ڂ̃X�v���C�g���J�E���g����

	
	cocos2d::Sprite* backcoin;
	//�X�R�A�̃X���C�h�����Đ�����
	void PlayAudioRanking() {
	cocos2d::experimental::AudioEngine::play2d("Sounds/SlideSE.ogg"); }
	//int compare_int(const void *a, const void *b);
	//�����L���O�̖��O
	std::string  RankingName[5];

	//�f�o�b�N�p
	cocos2d::Label* L_PlayerName[5];
	//
	std::string PlayerName[5];

	//����̃����L���O
	int m_now_ranking;
};


