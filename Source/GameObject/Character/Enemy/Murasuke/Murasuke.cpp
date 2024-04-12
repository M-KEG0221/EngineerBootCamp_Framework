#include "Murasuke.h"
#include "../../../../SystemTypes.h"
#include "DxLib.h"

Murasuke::Murasuke()
// Murasuke::Murasuke(SceneBase* owner_scene)
// :Enemy(owner_scene)
{
	hp = 2;
	current_direction_state = DirectionState::LEFT;
	current_enemy_state = EnemyState::IDLE;
	collisions["body"] = new BoxCollisionParams(
		BoxCollisionParams::CollisionObjectType::ENEMY,
		BoxCollisionParams::CollisionType::BLOCK,
		Vector2D(32.0f, 50.0f));
	body_collision = collisions["body"];
	SetDeltaPosition(Vector2D(0, 0));
	SetCurrentDirectionState(DirectionState::LEFT);
}

Murasuke::~Murasuke()
{
	// Finalize();
}

void Murasuke::Initialize()
{
	__super::Initialize();

	// 画像の読み込み
	// HACK: グラフィックマネージャーを作ったら直す
	LoadDivGraph(_T("Resources/Images/murasuke_pp_wait.bmp"), max_idle_flame, max_idle_flame, 1, 40, 48, graphic_handle_idle);
	LoadDivGraph(_T("Resources/Images/murasuke_pp_walk.bmp"), max_run_flame, max_run_flame, 1, 40, 48, graphic_handle_run);
	LoadDivGraph(_T("Resources/Images/murasuke_pp_damage.bmp"), max_damage_flame, max_damage_flame, 1, 40, 48, graphic_handle_damage);
}

void Murasuke::Update(float delta_seconds)
{
	__super::Update(delta_seconds);
	SetOldPosition(GetPosition());

	// 動かす
	Vector2D input_dir;

	// テスト用で簡単な動きになっている
	if (GetCurrentEnemyState() == EnemyState::RUN)
	{
		if (GetCurrentDirectionState() == DirectionState::LEFT)
		{
			input_dir.x = -1;
		}
		else
		{
			input_dir.x = 1;
		}
	}
	else if (GetCurrentEnemyState() == EnemyState::DEAD)
	{
		input_dir.x = 3;
		input_dir.y = -10;
	}
	ChangeEnemyState(EnemyState::RUN);

	UpdateAnimation();

	const float MOVEMENT_SPEED = 30.0f;
	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;
	if (GetCurrentEnemyState() == EnemyState::DEAD)
	{
		delta_position *= 25;
	}
	SetPosition(GetPosition() + delta_position);

	body_collision->Update(delta_seconds, GetPosition());

	// TODO: dead時、カメラ範囲+NNN離れたら自分を削除
}

void Murasuke::UpdateAnimation()
{
	switch (GetCurrentEnemyState())
	{
	case EnemyState::IDLE:
	{
		graphic_handle = graphic_handle_idle[graphic_idle_flame];

		break;
	}
	case EnemyState::RUN:
	{
		if (run_flame_adjust == run_flame_delay)
		{
			run_flame_adjust = 0;
			graphic_run_flame++;
		}
		if (graphic_run_flame == max_run_flame)
		{
			graphic_run_flame = 0;
		}

		run_flame_adjust++;

		graphic_handle = graphic_handle_run[graphic_run_flame];

		break;
	}
	case EnemyState::DEAD:
	{
		graphic_handle = graphic_handle_damage[graphic_damage_flame];
	}
	}
}

void Murasuke::Draw(const Vector2D &screen_offset)
{
	__super::Draw(screen_offset);

	// ????`??
	int x, y;
	GetPosition().ToInt(x, y);

	//???E???]????
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

	body_collision->Draw(screen_offset);

	body_collision->GetCenterPosition().ToInt(x, y);
	char str[256];
	sprintf_s(str, sizeof(str), "x: %d, y: %d", x, y);
	DrawString(0, 20, (const TCHAR *)str, GetColor(255, 255, 255));
}

void Murasuke::Finalize()
{
	__super::Finalize();

	for (int graphic : graphic_handle_idle)
	{
		//????j??
		DeleteGraph(graphic);
		graphic = 0;
	}

	for (int graphic : graphic_handle_run)
	{
		//????j??
		DeleteGraph(graphic);
		graphic = 0;
	}
}

void Murasuke::OnHitBoxCollision(const GameObject *hit_object, const BoxCollisionParams &hit_collision_params)
{
	// todo[]:各コリジョン（body, attack）ごとに当たっているかどうかを検査する
	switch (hit_collision_params.GetCollisionObjectType())
	{
	case BoxCollisionParams::CollisionObjectType::GROUND:
	{
		if (GetCurrentEnemyState() != EnemyState::DEAD)
		{

			float x = body_collision->center_position.x;
			float y = body_collision->center_position.y;
			float width = body_collision->box_size.x;
			float height = body_collision->box_size.y;
			float old_x = body_collision->old_center_position.x;
			float old_y = body_collision->old_center_position.y;

			float hit_x = hit_collision_params.GetCenterPosition().x;
			float hit_y = hit_collision_params.GetCenterPosition().y;
			float hit_width = hit_collision_params.GetBoxSize().x;
			float hit_height = hit_collision_params.GetBoxSize().y;

			Vector2D new_position = body_collision->GetCenterPosition();

			BoxHitResult my_result = GetBodyCollision()->HitCheckTarget(hit_collision_params);

			// NOTE:水平方向

			// NOTE: あくまで「横にめり込んでるオブジェクト」に対しての処理なので、それ以外のオブジェクトとの関係は気にしてない
			bool is_touch_vertical_side = my_result.IsTouchVerticalSide();

			if (my_result.is_hit_left_side && !is_touch_vertical_side)
			{
				new_position.x = hit_x + hit_width;
			}
			if (my_result.is_hit_right_side && !is_touch_vertical_side)
			{
				new_position.x = hit_x - width;
			}

			// 先に水平方向を修正して、斜めジャンプなどで壁に引っかからないようにする
			body_collision->SetCenterPosition(new_position);
			my_result = GetBodyCollision()->HitCheckTarget(hit_collision_params);
			// printfDx("X<%f,", new_position.x);
			// printfDx("%f>\n", hit_x + hit_width);

			// 垂直方向

			// 水平方向に対象と接しているときは押し出し処理を行わないようにする(斜め接触対策)
			bool is_touch_horizontal_side = my_result.IsTouchHorizontalSide();

			if (my_result.is_hit_top_side && !is_touch_horizontal_side)
			{
				new_position.y = hit_y + hit_height;

				// speed_y = 0.0f;
			}
			if (my_result.is_hit_under_side && !is_touch_horizontal_side)
			{
				// HandleLanding();
				new_position.y = hit_y - height;
			}

			if (my_result.is_touch_under_side)
			{
				// HandleLanding();
			}

			body_collision->SetCenterPosition(new_position);
			my_result = GetBodyCollision()->HitCheckTarget(hit_collision_params);

			if (!hitResult.is_touch_under_side && my_result.is_touch_under_side && my_result.IsTouchHorizontalSide())
			{
				// is_ground = false;
			}

			// 当たり判定の結果更新
			if (!hitResult.is_touch_left_side)
			{
				hitResult.is_touch_left_side = my_result.is_hit_left_side || my_result.is_touch_left_side;
			};
			if (!hitResult.is_touch_left_side)
			{
				hitResult.is_touch_right_side = my_result.is_hit_right_side || my_result.is_touch_right_side;
			};
			if (!hitResult.is_touch_left_side)
			{
				hitResult.is_touch_top_side = my_result.is_hit_top_side || my_result.is_touch_top_side;
			};
			if (!hitResult.is_touch_left_side)
			{
				hitResult.is_touch_under_side = my_result.is_hit_under_side || my_result.is_touch_under_side;
			};

			body_collision->SetCenterPosition(new_position);
			SetPosition(new_position - GetDeltaPosition());
			break;
		}
	}

	case BoxCollisionParams::CollisionObjectType::PLAYER:
	{
		if (hit_collision_params.GetCollisionType() == BoxCollisionParams::CollisionType::OVERLAP) // 攻撃
		{

			// todo: おそらくダメージ処理は、ダメージを受ける側ですべて判断する
			// todo: 敵側がplayerの攻撃に当たったと判断したら自分にダメージを与える？
			OnDamaged(1);
		}
	}
	}
}

void Murasuke::OnDamaged(int damage)
{
	ApplyDamage(damage);
}

void Murasuke::ApplyDamage(int damage)
{
	// printfDx("ApplyDamage: %d - %d\n", hp, damage);

	if (hp - damage < 0)
	{
		hp = 0;
	}
	else
	{
		hp = hp - damage;
	}

	if (hp <= 0)
	{
		ChangeEnemyState(EnemyState::DEAD);
	}
	// printfDx(_T("%d\n"), hp);
}