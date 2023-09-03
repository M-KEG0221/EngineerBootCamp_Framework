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

protected:
	EnemyState current_enemy_state;
	void ChangeEnemyState(EnemyState s);
	void OnEnterEnemyState(EnemyState s);
	void OnLeaveEnemyState(EnemyState s);

private:
};

