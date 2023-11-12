#pragma once
#include "DxLib.h"
#include "../Character.h"

#include "vector"
/**
 * キャラクター
 * サンプル用に簡易的に実装
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

	//IDLE状態アニメーション情報
	const static int max_idle_flame = 4;
	const int idle_flame_delay = 120;// まばたきアニメーションに入るまでの時間
	const int wink_flame_delay = 5;// まばたきアニメーション間の時間
	int idle_flame_adjust = 0;// delayかけてフレーム遷移するための値
	int graphic_handle_idle[max_idle_flame] = { 0,0,0,0 };
	int graphic_idle_flame = 0;

	//RUN状態アニメーション情報
	const static int max_run_flame = 8;
	const int run_flame_delay = 3;// 次の走りフレームに入るまでの時間
	int run_flame_adjust = 0;// delayかけてフレーム遷移するための値
	int graphic_handle_run[max_run_flame] = { 0,0,0,0, 0,0,0,0, };
	int graphic_run_flame = 0;

	const float jump_inital_speed = -2000.0f;
	float speed_y = 0.0f;

	//JUPM状態アニメーション情報
	const static int max_jump_flame = 6;//各種類ごとのフレーム
	const int jump_flame_delay = 3;
	const int jump_flame_branch_speed = 150;// 次のジャンプフレームに入る起点となる速度
	int jump_flame_point;//各ジャンプ画像の起点（0, 2, 4）
	bool toggle_jump_image = 0;//各ジャンプの画像を切り替える
	int jump_flame_adjust = 0;// delayかけてフレーム遷移するための値
	int graphic_handle_jump[max_jump_flame] = { 0,0, 0,0, 0,0, };
	int graphic_jump_flame = 0;

	//playerState関係
	PlayerState current_player_state;
	void ChangePlayerState(PlayerState s);
	void OnEnterPlayerState(PlayerState s);
	void OnLeavePlayerState(PlayerState s);

	void HandleLanding();
};

