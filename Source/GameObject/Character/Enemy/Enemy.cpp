#include "Enemy.h";

//enum class Enemy::EnemyState
//{
//	IDLE, RUN, ATTACK, DEAD
//};

void Enemy::ChangeEnemyState(EnemyState s)
{
	OnLeaveEnemyState(current_enemy_state);
	current_enemy_state = s;
	OnEnterEnemyState(current_enemy_state);
}
void Enemy::OnEnterEnemyState(EnemyState s)
{

}

void Enemy::OnLeaveEnemyState(EnemyState s)
{

}