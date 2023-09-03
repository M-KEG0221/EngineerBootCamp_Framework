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
	enum class PlayerState;
	/*{
		IDLE, RUN,
	};*/

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

	void UpdateAnimation() override;

	PlayerState GetCuurentPlayerState() const { return current_player_state; }
	//PlayerDirectionState getHorizontalDirectionState() const { return currentDirectionState; }

private:
	//IDLE��ԃA�j���[�V�������
	const static int max_idle_flame = 4;
	const static int idle_flame_delay = 120;// �܂΂����A�j���[�V�����ɓ���܂ł̎���
	const static int wink_flame_delay = 5;// �܂΂����A�j���[�V�����Ԃ̎���
	int idle_flame_adjust = 0;// delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphic_handle_idle[max_idle_flame] = { 0,0,0,0 };
	int graphic_idle_flame = 0;

	//RUN��ԃA�j���[�V�������
	const static int max_run_flame = 8;
	const static int run_flame_delay = 3;// ���̑���t���[���ɓ���܂ł̎���
	int run_flame_adjust = 0;// delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphic_handle_run[max_run_flame] = { 0,0,0,0 };
	int graphic_run_flame = 0;

	//playerState�֌W
	PlayerState current_player_state;
	void ChangePlayerState(PlayerState s);
	void OnEnterPlayerState(PlayerState s);
	void OnLeavePlayerState(PlayerState s);
};
