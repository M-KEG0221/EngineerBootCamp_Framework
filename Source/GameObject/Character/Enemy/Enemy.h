#pragma once
#include "../Character.h"

class Enemy abstract :public Character
{
protected:
	enum class EnemyState
	{
		IDLE, RUN, ATTACK, DEAD
	};

public:
	EnemyState GetCurrentEnemyState() { return current_enemy_state; }
	void OnHitBoxCollision(const GameObject* hit_object, const BoxCollisionParams& hit_collision_params) override;

protected:
	EnemyState current_enemy_state;
	void ChangeEnemyState(EnemyState s);
	void OnEnterEnemyState(EnemyState s);
	void OnLeaveEnemyState(EnemyState s);

private:
};

