#include "Player.h"
#include "../Character.h"

#include "DxLib.h"

enum class Player::PlayerState
{
	IDLE, RUN, JUMP,
};

Player::Player()
{
	current_direction_state = DirectionState::RIGHT;
	body_collision = new BoxCollisionParams
	(
		BoxCollisionParams::CollisionObjectType::PLAYER,
		BoxCollisionParams::CollisionType::BLOCK,
		Vector2D(32.0f, 50.0f)
	);

	SetDeltaPosition(Vector2D(48, 60));
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
}

void Player::Update(float delta_seconds)
{
	__super::Update(delta_seconds);

	SetOldPosition(GetPosition());

	// 動かす
	Vector2D input_dir;
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		input_dir.x = -1;
		/*if (current_player_state == PlayerState::IDLE)
		{*/
		ChangePlayerState(PlayerState::RUN);
		//}
		SetCurrentDirectionState(DirectionState::LEFT);
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
		/*if (current_player_state == PlayerState::IDLE)
		{*/
		ChangePlayerState(PlayerState::RUN);
		//}
		SetCurrentDirectionState(DirectionState::RIGHT);
	}
	else
	{
		ChangePlayerState(PlayerState::IDLE);
		//hp--;
	}

	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		//TODO: jump
		if (current_player_state != PlayerState::JUMP)
		{
			//ChangePlayerState(PlayerState::JUMP);
			input_dir.y = -1 * jump_inital_speed;
		}
	}
	else if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		// NOTE: しゃがみ？すり抜け床で使用
		input_dir.y = 1;
	}

	Vector2D delta_position = input_dir/*.Normalize()*/ * MOVEMENT_SPEED * delta_seconds;
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
		if (speed_y < jump_flame_branch)
		{

		}
		else if (speed_y >= jump_flame_branch)
		{

		}
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
	OnLeavePlayerState(current_player_state);
	current_player_state = s;
	OnEnterPlayerState(current_player_state);
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
		/*case PlayerState::IDLE:
			idle_flame_adjust = 0;
			graphic_idle_flame = 0;
			break;
		case PlayerState::RUN:
			run_flame_adjust = 0;
			graphic_run_flame = 0;*/
	}

}

void Player::OnHitBoxCollision(const GameObject* hit_object, const BoxCollisionParams& hit_collision_params)
{
	BoxHitResult result = GetBodyCollision()->HitCheckTarget(hit_collision_params);

	BoxCollisionParams::CollisionType block = BoxCollisionParams::CollisionType::BLOCK;
	switch (hit_collision_params.GetCollisionType())
	{
	case BoxCollisionParams::CollisionType::BLOCK:
		int x, y, width, height;
		body_collision->GetCenterPosition().ToInt(x, y);
		body_collision->GetBoxExtent().ToInt(width, height);

		int hit_x, hit_y, hit_width, hit_height;
		hit_collision_params.GetCenterPosition().ToInt(hit_x, hit_y);
		hit_collision_params.GetBoxExtent().ToInt(hit_width, hit_height);

		int new_x, new_y;
		GetOldPosition().ToInt(new_x, new_y);

		int delta_x, delta_y;
		GetDeltaPosition().ToInt(delta_x, delta_y);

		if (result.is_hit_left_side)
		{
			printfDx("左\n");
			new_x = hit_x + hit_width - delta_x;
		}
		if (result.is_hit_right_side)
		{
			printfDx("右\n");
			new_x = hit_x - width - delta_x;
		}
		if (result.is_hit_top_side)
		{
			printfDx("上\n");
			new_y = hit_y + hit_height - delta_y;
			speed_y = 0;
		}
		if (result.is_hit_under_side)
		{
			printfDx("下\n");
			new_y = hit_y - height - delta_y /*- 1*/;
			ChangePlayerState(PlayerState::IDLE);
		}

		SetPosition(Vector2D(new_x, new_y));
		body_collision->SetCenterPosition(Vector2D(new_x, new_y) + delta_position);
		break;
	}

	//SetPosition(GetOldPosition());
}