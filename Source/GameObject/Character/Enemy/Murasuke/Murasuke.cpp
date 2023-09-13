#include "Murasuke.h"
#include "../../../../SystemTypes.h"
#include "DxLib.h"

Murasuke::Murasuke()
{
	current_direction_state = DirectionState::LEFT;
	current_enemy_state = EnemyState::IDLE;
}

Murasuke::~Murasuke()
{
	//Finalize();
}

void Murasuke::Initialize()
{
	__super::Initialize();

	// 画像の読み込み
	// HACK: グラフィックマネージャーを作ったら直す
	LoadDivGraph(_T("Resources/Images/murasuke_pp_wait.bmp"), max_idle_flame, max_idle_flame, 1, 40, 48, graphic_handle_idle);
	LoadDivGraph(_T("Resources/Images/murasuke_pp_walk.bmp"), max_run_flame, max_run_flame, 1, 40, 48, graphic_handle_run);
}

void Murasuke::Update(float delta_seconds)
{
	__super::Update(delta_seconds);

	// 動かす
	Vector2D input_dir;

	input_dir.x = -1;
	ChangeEnemyState(EnemyState::RUN);
	SetCurrentDirectionState(DirectionState::LEFT);

	UpdateAnimation();

	const float MOVEMENT_SPEED = 30.0f;
	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;
	SetPosition(GetPosition() + delta_position);
}

// 画像の描画設定
void Murasuke::UpdateAnimation()
{
	switch (GetCurrentEnemyState())
	{
	case EnemyState::IDLE:

		graphic_handle = graphic_handle_idle[graphic_idle_flame];

		break;

	case EnemyState::RUN:
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

void Murasuke::Draw(const Vector2D& screen_offset)
{
	__super::Draw(screen_offset);

	// 画像の描画
	int x, y;
	GetPosition().ToInt(x, y);

	//左右反転処理
	if (GetCurrentDirectionState() == DirectionState::RIGHT)
	{
		DrawTurnGraph(x, y, graphic_handle, true);
	}
	else if (GetCurrentDirectionState() == DirectionState::LEFT)
	{
		DrawGraph(x, y, graphic_handle, true);
	}

	if (x < -50)
	{
		Vector2D new_position = Vector2D(SCREEN_RESOLUTION_X, y);
		SetPosition(new_position);
	}
}

void Murasuke::Finalize()
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