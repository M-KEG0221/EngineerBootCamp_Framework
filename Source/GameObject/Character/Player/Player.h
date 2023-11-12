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

public:
	Player();
	virtual ~Player();

public:
	//~ Begin GameObject interface
	void Initialize() override;
	void Update(float delta_seconds) override;
	void Draw(const Vector2D& screen_offset) override;
	void Finalize() override;
	void OnHitBoxCollision(const GameObject* hit_object, const BoxCollisionParams& hit_collision_params) override;
	void OnNoHitBoxCollision() override;
	//~ End GameObject interface

	void UpdateAnimation() override;

	PlayerState GetCuurentPlayerState() const { return current_player_state; }
	//PlayerDirectionState getHorizontalDirectionState() const { return currentDirectionState; }


private:
	bool is_ground = false;
	bool is_jumping = false;
	float jumping_seconds = 0.0f;
	const float MOVEMENT_SPEED = 300.0f;

	//IDLE��ԃA�j���[�V�������
	const static int max_idle_flame = 4;
	const int idle_flame_delay = 120;// �܂΂����A�j���[�V�����ɓ���܂ł̎���
	const int wink_flame_delay = 5;// �܂΂����A�j���[�V�����Ԃ̎���
	int idle_flame_adjust = 0;// delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphic_handle_idle[max_idle_flame] = { 0,0,0,0 };
	int graphic_idle_flame = 0;

	//RUN��ԃA�j���[�V�������
	const static int max_run_flame = 8;
	const int run_flame_delay = 3;// ���̑���t���[���ɓ���܂ł̎���
	int run_flame_adjust = 0;// delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphic_handle_run[max_run_flame] = { 0,0,0,0, 0,0,0,0, };
	int graphic_run_flame = 0;

	const float jump_inital_speed = -2000.0f;
	float speed_y = 0.0f;

	//JUPM��ԃA�j���[�V�������
	const static int max_jump_flame = 6;//�e��ނ��Ƃ̃t���[��
	const int jump_flame_delay = 3;
	const int jump_flame_branch_speed = 150;// ���̃W�����v�t���[���ɓ���N�_�ƂȂ鑬�x
	int jump_flame_point;//�e�W�����v�摜�̋N�_�i0, 2, 4�j
	bool toggle_jump_image = 0;//�e�W�����v�̉摜��؂�ւ���
	int jump_flame_adjust = 0;// delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphic_handle_jump[max_jump_flame] = { 0,0, 0,0, 0,0, };
	int graphic_jump_flame = 0;

	//playerState�֌W
	PlayerState current_player_state;
	void ChangePlayerState(PlayerState s);
	void OnEnterPlayerState(PlayerState s);
	void OnLeavePlayerState(PlayerState s);

	void HandleLanding();
};

