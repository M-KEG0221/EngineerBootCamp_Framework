#include "Enemy.h";
#include "../../../Utility/BoxCollisionParams.h";
// enum class Enemy::EnemyState
//{
//	IDLE, RUN, ATTACK, DEAD
// };

void Enemy::ChangeEnemyState(EnemyState s)
{
	if (!(current_enemy_state == s || current_enemy_state == EnemyState::DEAD))
	{
		OnLeaveEnemyState(current_enemy_state);
		EnemyState old_state = current_enemy_state;
		current_enemy_state = s;
		OnEnterEnemyState(old_state);
	}
}
void Enemy::OnEnterEnemyState(EnemyState s)
{
	if (s == EnemyState::DEAD)
	{
		// collisions['body'];
		// body_collision->GetCollisionType()->SetCollisionType(CollisionType::OVERLAP);
		body_collision->SetCollisionType(BoxCollisionParams::CollisionType::OVERLAP);
	}
}

void Enemy::OnLeaveEnemyState(EnemyState s)
{
	if (s == EnemyState::DEAD)
	{
		current_enemy_state = s;
	}
}

void Enemy::OnHitBoxCollision(const GameObject *hit_object, const BoxCollisionParams &hit_collision_params)
{
	BoxHitResult result = GetBodyCollision()->HitCheckTarget(hit_collision_params);

	BoxCollisionParams::CollisionType block = BoxCollisionParams::CollisionType::BLOCK;
	switch (hit_collision_params.GetCollisionType())
	{
	case BoxCollisionParams::CollisionType::BLOCK:
		if (GetCurrentEnemyState() == EnemyState::DEAD)
		{

			int x, y, width, height;
			body_collision->GetCenterPosition().ToInt(x, y);
			body_collision->GetBoxSize().ToInt(width, height);

			int hit_x, hit_y, hit_width, hit_height;
			hit_collision_params.GetCenterPosition().ToInt(hit_x, hit_y);
			hit_collision_params.GetBoxSize().ToInt(hit_width, hit_height);

			int new_x, new_y;
			GetOldPosition().ToInt(new_x, new_y);

			int delta_x, delta_y;
			GetDeltaPosition().ToInt(delta_x, delta_y);

			if (result.is_hit_left_side)
			{
				printfDx("E¶");
				new_x = hit_x + hit_width - delta_x + 1;
			}
			if (result.is_hit_right_side)
			{
				printfDx("E‰E");
				new_x = hit_x - width - delta_x - 1;
			}
			if (result.is_hit_top_side)
			{
				printfDx("Eã");
				new_y = hit_y + hit_height - delta_y + 1;
			}
			if (result.is_hit_under_side)
			{
				printfDx("E‰º");
				new_y = hit_y - height - delta_y - 1;
			}

			SetPosition(Vector2D(new_x, new_y));
			body_collision->SetCenterPosition(Vector2D(new_x, new_y) + delta_position);
			break;
		}
	}
}