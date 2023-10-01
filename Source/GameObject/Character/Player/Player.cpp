#include "Player.h"
#include "../Character.h"

#include "DxLib.h"

enum class Player::PlayerState
{
	IDLE, RUN, JUMP,
};

//enum class Player::GroundState
//{
//	IDLE, RUN
//};
//
//enum class Player::PlayerState
//{
//	IDLE, RUN, JUMP,
//};

Player::Player()
{
	current_direction_state = DirectionState::RIGHT;
	body_collision = new BoxCollisionParams
	(
		BoxCollisionParams::CollisionObjectType::PLAYER,
		BoxCollisionParams::CollisionType::BLOCK,
		Vector2D(30.0f, 50.0f)
	);

	SetDeltaPosition(Vector2D(50, 60));
}

Player::~Player()
{
	//Finalize();
}

void Player::Initialize()
{
	__super::Initialize();

	// 画像の読み込み
	// HACK: グラフィックマネージャーを作ったら直す
	LoadDivGraph(_T("Resources/Images/collon_wait_a.bmp"), max_idle_flame, max_idle_flame, 1, 128, 128, graphic_handle_idle);
	LoadDivGraph(_T("Resources/Images/collon_run8.bmp"), max_run_flame, 4, 2, 128, 128, graphic_handle_run);
	LoadDivGraph(_T("Resources/Images/collon_jump.bmp"), max_jump_flame, 4, 2, 128, 128, graphic_handle_jump);
}

void Player::Update(float delta_seconds)
{
	__super::Update(delta_seconds);

	/*if (!is_ground)
	{
	}*/

	// 動かす
	Vector2D input_dir;
	if (!is_ground)
	{
		ChangePlayerState(PlayerState::JUMP);
		input_dir.y = 1;
	}

	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		input_dir.x = -1;
		if (is_ground)
		{
			ChangePlayerState(PlayerState::RUN);
		}
		SetCurrentDirectionState(DirectionState::LEFT);
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
		if (is_ground)
		{
			ChangePlayerState(PlayerState::RUN);
		}
		SetCurrentDirectionState(DirectionState::RIGHT);
	}
	else
	{
		if (is_ground)
		{
			ChangePlayerState(PlayerState::IDLE);
		}
	}

	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		//TODO: jump
		if (is_ground)
		{
			is_ground = false;
			ChangePlayerState(PlayerState::JUMP);
			speed_y = jump_inital_speed;//TODO: wキーを押した時間だけ掛け算する。（initalも合わせて修正する）
		}
	}
	//else if (CheckHitKey(KEY_INPUT_S) == 1)
	if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		// NOTE: しゃがみ？すり抜け床で使用
	}

	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;

	//ChangePlayerState(PlayerState::JUMP);

	if (!is_ground)
	{
		delta_position.y = delta_position.y + speed_y * delta_seconds;
		speed_y = speed_y + GRAVITY * delta_seconds;
		if (speed_y >= MAX_FALL_SPEED)
		{
			speed_y = MAX_FALL_SPEED;
		}
		else if (speed_y <= MAX_FALL_SPEED * -1)
		{
			speed_y = MAX_FALL_SPEED * -1;
		}
	}

	SetOldPosition(GetPosition());
	SetPosition(GetPosition() + delta_position);

	body_collision->Update(delta_seconds, GetPosition(), GetDeltaPosition());

	UpdateAnimation();
}

// 画像の描画設定
void Player::UpdateAnimation()
{
	// NOTE: このままだとキーを反転しても途中のflameから描画されるため注意

	boolean canMoveNextWinkFlame = (idle_flame_adjust - idle_flame_delay) % wink_flame_delay == 0;

	switch (GetCuurentPlayerState())
	{
	case PlayerState::IDLE:

		if (idle_flame_adjust >= idle_flame_delay && canMoveNextWinkFlame)//120fたったら瞬きモーションに入る。5fごとにフレームを動かす
		{
			graphic_idle_flame++;
		}
		if (graphic_idle_flame == max_idle_flame)//最後の瞬きモーションが終わったらリセットする
		{
			idle_flame_adjust = 0;
			graphic_idle_flame = 0;
		}

		idle_flame_adjust++;

		graphic_handle = graphic_handle_idle[graphic_idle_flame];

		break;

	case PlayerState::RUN:
		if (run_flame_adjust == run_flame_delay)//一定f立ったら次のモーションに移る
		{
			run_flame_adjust = 0;
			graphic_run_flame++;
		}
		if (graphic_run_flame == max_run_flame)//最後のモーションが終わったらリセットする
		{
			graphic_run_flame = 0;
		}

		run_flame_adjust++;

		graphic_handle = graphic_handle_run[graphic_run_flame];

		break;
	case PlayerState::JUMP:
		if (speed_y < -jump_flame_branch)
		{
			jump_flame_point = 0;

		}
		else if (-jump_flame_branch <= speed_y && speed_y < jump_flame_branch)
		{
			jump_flame_point = 2;
		}
		else if (speed_y >= jump_flame_branch)
		{
			jump_flame_point = 4;
		}

		if (jump_flame_adjust == jump_flame_delay)
		{
			toggle_jump_image = !toggle_jump_image;
			jump_flame_adjust = 0;
		}

		jump_flame_adjust++;

		graphic_jump_flame = jump_flame_point + toggle_jump_image;

		//printfDx("flame: %d\n", toggle_jump_image);
		//printfDx("%d\n", graphic_jump_flame);
		graphic_handle = graphic_handle_jump[graphic_jump_flame];
		break;
	}
}

void Player::Draw(const Vector2D& screen_offset)
{
	__super::Draw(screen_offset);

	// 画像の描画
	int x, y;
	GetPosition().ToInt(x, y);

	//左右反転処理
	if (GetCurrentDirectionState() == DirectionState::LEFT)
	{
		DrawTurnGraph(x, y, graphic_handle, true);
	}
	else if (GetCurrentDirectionState() == DirectionState::RIGHT)
	{
		DrawGraph(x, y, graphic_handle, true);
	}

	//body_collision->center_position = Vector2D(x + 48, y + 60);
	body_collision->Draw(screen_offset);

	body_collision->GetCenterPosition().ToInt(x, y);
	char str[256];
	sprintf_s(str, sizeof(str), "x: %d, y: %d", x, y);
	DrawString(0, 0, str, GetColor(255, 255, 255));
}

void Player::Finalize()
{
	__super::Finalize();

	for (int graphic : graphic_handle_idle)
	{
		//画像の破棄
		DeleteGraph(graphic);
		graphic = 0;
	}

	for (int graphic : graphic_handle_run)
	{
		//画像の破棄
		DeleteGraph(graphic);
		graphic = 0;
	}
}

void Player::ChangePlayerState(PlayerState s)
{
	if (current_player_state != s)
	{
		OnLeavePlayerState(current_player_state);
		current_player_state = s;
		OnEnterPlayerState(current_player_state);
	}
}

void Player::OnEnterPlayerState(PlayerState s)
{
	/*switch (s)
	{
		case PlayerState:
	}*/
}

void Player::OnLeavePlayerState(PlayerState s)
{
	switch (s)
	{
	case PlayerState::IDLE:
		idle_flame_adjust = 0;
		graphic_idle_flame = 0;
		break;
	case PlayerState::RUN:
		run_flame_adjust = 0;
		graphic_run_flame = 0;
		break;
	case PlayerState::JUMP:
		jump_flame_adjust = 0;
		graphic_jump_flame = 0;
		toggle_jump_image = 0;
		break;
	}


}

void Player::OnHitBoxCollision(const GameObject* hit_object, const BoxCollisionParams& hit_collision_params)
{

	switch (hit_collision_params.GetCollisionObjectType())
	{
	case BoxCollisionParams::CollisionObjectType::GROUND:
		float x = body_collision->center_position.x;
		float y = body_collision->center_position.y;
		float width = body_collision->box_extent.x;
		float height = body_collision->box_extent.y;
		float old_x = body_collision->old_center_position.x;
		float old_y = body_collision->old_center_position.y;

		float hit_x = hit_collision_params.GetCenterPosition().x;
		float hit_y = hit_collision_params.GetCenterPosition().y;
		float hit_width = hit_collision_params.GetBoxExtent().x;
		float hit_height = hit_collision_params.GetBoxExtent().y;

		Vector2D new_position = body_collision->GetCenterPosition();

		BoxHitResult result = GetBodyCollision()->HitCheckTarget(hit_collision_params);

		//水平方向

		//垂直方向に対象と接しているときは押し出し処理を行わないようにする
		bool is_touch_vertical_side = result.IsTouchVerticalSide();

		if (result.is_hit_left_side && !is_touch_vertical_side)
		{
			new_position.x = hit_x + hit_width;
		}
		if (result.is_hit_right_side && !is_touch_vertical_side)
		{
			new_position.x = hit_x - width;
		}

		//先に水平方向を修正して、斜めジャンプなどで壁に引っかからないようにする
		body_collision->SetCenterPosition(new_position);
		result = GetBodyCollision()->HitCheckTarget(hit_collision_params);
		printfDx("X<%f,", new_position.x);
		printfDx("%f>\n", hit_x + hit_width);

		//垂直方向

		//水平方向に対象と接しているときは押し出し処理を行わないようにする
		bool is_touch_horizontal_side = result.IsTouchHorizontalSide();

		if (result.is_hit_top_side && !is_touch_horizontal_side)
		{
			new_position.y = hit_y + hit_height;

			speed_y = 0.0f;
		}
		if (result.is_hit_under_side && !is_touch_horizontal_side)
		{
			/*is_ground = true;
			speed_y = 0.0f;*/
			HandleLanding();
			new_position.y = hit_y - height;

		}

		if (result.is_touch_under_side)
		{
			/*is_ground = true;
			speed_y = 0.0f;*/
			HandleLanding()
		}

		body_collision->SetCenterPosition(new_position);
		result = GetBodyCollision()->HitCheckTarget(hit_collision_params);

		if (!hitResult.is_touch_under_side && result.is_touch_under_side && result.IsTouchHorizontalSide())
		{
			is_ground = false;
		}

		//当たり判定の結果更新
		if (!hitResult.is_touch_left_side) {
			hitResult.is_touch_left_side = result.is_hit_left_side || result.is_touch_left_side;
		};
		if (!hitResult.is_touch_left_side) {
			hitResult.is_touch_right_side = result.is_hit_right_side || result.is_touch_right_side;
		};
		if (!hitResult.is_touch_left_side) {
			hitResult.is_touch_top_side = result.is_hit_top_side || result.is_touch_top_side;
		};
		if (!hitResult.is_touch_left_side) {
			hitResult.is_touch_under_side = result.is_hit_under_side || result.is_touch_under_side;
		};


		printfDx("Y<%f,", new_position.y + height);
		printfDx("%f>\n", hit_y);

		if (result.is_hit_left_side)
		{
			printfDx("left\n");
		}
		if (result.is_hit_right_side)
		{
			printfDx("right\n");
		}
		if (result.is_hit_top_side)
		{
			printfDx("top\n");
		}
		if (result.is_hit_under_side)
		{
			printfDx("under\n");
		}

		if (result.is_touch_left_side)
		{
			printfDx("touch left\n");
		}
		if (result.is_touch_right_side)
		{
			printfDx("touch right\n");
		}
		if (result.is_touch_top_side)
		{
			printfDx("touch top\n");
		}
		if (result.is_touch_under_side)
		{
			printfDx("touch under\n");
		}
		printfDx("------\n\n");

		int delta_x, delta_y;
		GetDeltaPosition().ToInt(delta_x, delta_y);
		Vector2D delta = GetDeltaPosition();

		body_collision->SetCenterPosition(new_position);
		SetPosition(new_position - GetDeltaPosition());
		break;
	}
}

/*
* プレイヤーが着地した際の処理をまとめて実行する
*/
void Player::HandleLanding()
{
	is_ground = true;
	is_jumping = false;
	speed_y = 0.0f;

}

void Player::OnNoHitBoxCollision()
{
	is_ground = false;
	ChangePlayerState(PlayerState::JUMP);
	printfDx("NO");
}
