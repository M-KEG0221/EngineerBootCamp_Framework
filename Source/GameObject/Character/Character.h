#pragma once
#include "../GameObject.h"

/**
 * �L�����N�^�[
 * �T���v���p�ɊȈՓI�Ɏ���
 */
class Character : public GameObject
{
	enum class playerState
	{
		IDLE, RUN,
	};

public:
	Character();
	virtual ~Character();

public:
	//~ Begin GameObject interface
	virtual void Initialize() override;
	void Update(float delta_seconds) override;
	void Draw(const Vector2D& screen_offset) override;
	void Finalize() override;
	playerState getState() const { return state; }
	//~ End GameObject interface

private:
	//Idle��ԃA�j���[�V�������
	const static int maxIdleFlame = 4;
	const static int idleFlameDelay = 120;// �܂΂����A�j���[�V�����ɓ���܂ł̎���
	const static int winkFlameDelay = 5;// �܂΂����A�j���[�V�����Ԃ̎���
	int idleFlameAdjust = 0;// delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphicHandleIdle[maxIdleFlame];
	int graphicIdleFlame;

	const static int maxRunFlame = 8;
	const static int runFlameDelay = 3;// ���̑���t���[���ɓ���܂ł̎���
	int runFlameAdjust = 0;// delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphicHandleRun[maxRunFlame];
	int graphicRunFlame;

	int hp;
	playerState state;

	void onEnterPlayerState(playerState s)
	{
		ChangePlayerState(s);
	}

	void ChangePlayerState(playerState s)
	{
		playerState oldState = s;
		onLeavePlayerState(oldState);
		state = s;
	}

	void onLeavePlayerState(playerState s)
	{
		
	}
};

