#include "Player.h"
#include "../Character.h"

#include "DxLib.h"

enum class Player::PlayerState
{
	IDLE, RUN,
};

Player::Player()
{
	current_direction_state = DirectionState::RIGHT;
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

	// 動かす
	Vector2D input_dir;
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		input_dir.x = -1;
		ChangePlayerState(PlayerState::RUN);
		SetCurrentDirectionState(DirectionState::LEFT);
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
		ChangePlayerState(PlayerState::RUN);
		SetCurrentDirectionState(DirectionState::RIGHT);
	}
	else
	{
		ChangePlayerState(PlayerState::IDLE);
		//hp--;
	}

	/*if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		//TODO: jump
		input_dir.y = -1;
	}
	else if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		// NOTE: しゃがみ？すり抜け床で使用
		input_dir.y = 1;
	}*/

	UpdateAnimation();

	const float MOVEMENT_SPEED = 300.0f;
	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;
	SetPosition(GetPosition() + delta_position);
}

void Player::UpdateAnimation()
{
	// NOTE: このままだとキーを反転しても途中のflameから描画されるため注意

	// 画像の描画
	boolean canMoveNextWinkFlame = (idle_flame_adjust - idle_flame_delay) % wink_flame_delay == 0;

	switch (GetCuurentPlayerState())
	{
	case PlayerState::IDLE:

		if (idle_flame_adjust >= idle_flame_delay && canMoveNextWinkFlame)//120fたったら瞬きモーションに入る。5fごとにフレームを動かす
		{
			graphic_idle_flame++;
			//printfDx("@@\n");
		}
		if (graphic_idle_flame == max_idle_flame)//最後の瞬きモーションが終わったらリセットする
		{
			idle_flame_adjust = 0;
			graphic_idle_flame = 0;
			//printfDx("リセット\n");
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
}

void Player::OnLeavePlayerState(PlayerState s)
{

}