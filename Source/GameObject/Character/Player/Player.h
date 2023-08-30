#pragma once
#include "DxLib.h"
#include "../Character.h"
#include "vector"

/**
 * �L�����N�^�[
 * �T���v���p�ɊȈՓI�Ɏ���
 */
class Player : public Character
{
	enum class PlayerState
	{
		IDLE, RUN,
	};
	enum class DirectionState
	{
		LEFT, RIGHT,
	};

public:
	Player();
	virtual ~Player();

public:
	//~ Begin GameObject interface
	void Initialize() override;
	void Update(float delta_seconds) override;
	void Draw(const Vector2D& screen_offset) override;
	void Finalize() override;
	//~ End GameObject interface
	PlayerState getState() const { return currentPlayerState; }
	DirectionState getHorizontalDirectionState() const { return currentDirectionState; }

private:
	//IDLE��ԃA�j���[�V�������
	const static int maxIdleFlame = 4;
	const static int idleFlameDelay = 120;// �܂΂����A�j���[�V�����ɓ���܂ł̎���
	const static int winkFlameDelay = 5;// �܂΂����A�j���[�V�����Ԃ̎���
	int idleFlameAdjust = 0;// delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphicHandleIdle[maxIdleFlame] = { 0,0,0,0 };
	int graphicIdleFlame = 0;

	//RUN��ԃA�j���[�V�������
	const static int maxRunFlame = 8;
	const static int runFlameDelay = 3;// ���̑���t���[���ɓ���܂ł̎���
	int runFlameAdjust = 0;// delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphicHandleRun[maxRunFlame] = { 0,0,0,0 };
	int graphicRunFlame = 0;

	//playerState�֌W
	PlayerState currentPlayerState;
	void ChangePlayerState(PlayerState s);
	void OnEnterPlayerState(PlayerState s);
	void OnLeavePlayerState(PlayerState s);

	//�L�����̌����֌W
	DirectionState currentDirectionState = DirectionState::RIGHT;
	void SetDirectionState(DirectionState hds) { currentDirectionState = hds; }
};

