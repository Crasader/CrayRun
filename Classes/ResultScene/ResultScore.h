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
#include "ResultLayer.h"
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

	//�����L���O�X�R�A
	int RankingScore[MAX_SCORE];
	//�X�R�A�̐ݒ�A�`��
	void ScoreIndicate(int Score);
	//����̃X�R�A
	static int m_Score;
private:

	cocos2d::UserDefault* userDefault;


	//�����X�v���C�g
	cocos2d::Sprite* s_Number;
	int ScoreMaxDigit;//�ő包��
	int SaveScore;//�X�R�A��ۑ�����
	int SaveScore2;
	int Digit;//����
	int SpriteCnt;//���ڂ̃X�v���C�g���J�E���g����

	//�����X�v���C�g���Ԃ牺����m�[�h
	cocos2d::Node* node_number[MAX_SCORE + 1];



};

