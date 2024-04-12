#pragma once
#include "../Character.h"

class Enemy abstract : public Character
{
protected:
	enum class EnemyState
	{
		IDLE,
		RUN,
		ATTACK,
		DAMAGE,
		DEAD
	};

public:
	EnemyState GetCurrentEnemyState() { return current_enemy_state; }
	void OnHitBoxCollision(const GameObject *hit_object, const BoxCollisionParams &hit_collision_params) override;

protected:
	EnemyState current_enemy_state;
	void ChangeEnemyState(EnemyState s);
	void OnEnterEnemyState(EnemyState s);
	void OnLeaveEnemyState(EnemyState s);

	virtual void ApplyDamage(int damage){};
	virtual void OnDamaged(int damage){};

	Enemy();
	Enemy(SceneBase* owner_scene);
	virtual ~Enemy();
private:
};
