#include "Player.h"

#include "DxLib.h"

Player::Player()
	:graphicIdleFlame(0)
	//graphicHandleIdle(maxIdleFlame)
{
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
	LoadDivGraph(_T("Resources/Images/collon_wait_a.bmp"), maxIdleFlame, maxIdleFlame, 1, 128, 128, graphicHandleIdle);
	LoadDivGraph(_T("Resources/Images/collon_run8.bmp"), maxRunFlame, 4, 2, 128, 128, graphicHandleRun);
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
		SetDirectionState(DirectionState::LEFT);
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
		ChangePlayerState(PlayerState::RUN);
		SetDirectionState(DirectionState::RIGHT);
	}
	else
	{
		ChangePlayerState(PlayerState::IDLE);
		hp--;
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

	const float MOVEMENT_SPEED = 300.0f;
	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;
	SetPosition(GetPosition() + delta_position);
}

void Player::Draw(const Vector2D& screen_offset)
{
	__super::Draw(screen_offset);

	// 画像の描画
	int x, y;
	GetPosition().ToInt(x, y);
	boolean canMoveNextWinkFlame = (idleFlameAdjust - idleFlameDelay) % winkFlameDelay == 0;

	switch (getState())
	{
	case PlayerState::IDLE:

		if (idleFlameAdjust >= idleFlameDelay && canMoveNextWinkFlame)//120fたったら瞬きモーションに入る。5fごとにフレームを動かす
		{
			graphicIdleFlame++;
			//printfDx("@@\n");
		}
		if (graphicIdleFlame == maxIdleFlame)//最後の瞬きモーションが終わったらリセットする
		{
			idleFlameAdjust = 0;
			graphicIdleFlame = 0;
			//printfDx("リセット\n");
		}

		idleFlameAdjust++;
		//DrawGraph(x, y, graphicHandleIdle[graphicIdleFlame], true);
		if (getHorizontalDirectionState() == DirectionState::LEFT)
		{
			DrawTurnGraph(x, y, graphicHandleIdle[graphicIdleFlame], true);
		}
		else if (getHorizontalDirectionState() == DirectionState::RIGHT)
		{
			DrawGraph(x, y, graphicHandleIdle[graphicIdleFlame], true);
		}
		break;

	case PlayerState::RUN:
		if (runFlameAdjust == runFlameDelay)//10f立ったら次のモーションに移る
		{
			runFlameAdjust = 0;
			graphicRunFlame++;
		}
		if (graphicRunFlame == maxRunFlame)//最後の瞬きモーションが終わったらリセットする
		{
			graphicRunFlame = 0;
		}

		runFlameAdjust++;

		//左右反転処理。
		// NOTE: ただしこのままだとキーを反転しても途中のflameから描画されるため注意
		if (CheckHitKey(KEY_INPUT_A))
		{
			DrawTurnGraph(x, y, graphicHandleRun[graphicRunFlame], true);
		}
		else if (CheckHitKey(KEY_INPUT_D) == 1)
		{
			DrawGraph(x, y, graphicHandleRun[graphicRunFlame], true);
		}
		break;

	}

}

void Player::Finalize()
{
	__super::Finalize();

	for (int graphic : graphicHandleIdle)
	{
		//画像の破棄
		DeleteGraph(graphic);
		graphic = 0;
	}
}

void Player::ChangePlayerState(PlayerState s)
{
	//OnLeavePlayerState(currentPlayerState);
	currentPlayerState = s;
	OnEnterPlayerState(s);
}

void Player::OnEnterPlayerState(PlayerState s)
{
}

void Player::OnLeavePlayerState(PlayerState s)
{

}