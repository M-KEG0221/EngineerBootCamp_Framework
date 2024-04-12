#pragma once
#include "../Enemy.h"
class Murasuke : public Enemy
{
public:
	Murasuke();
	Murasuke(SceneBase* owner_scene);
	~Murasuke();

public:
	//~ Begin GameObject interface
	void Initialize() override;
	void Update(float delta_seconds) override;
	void Draw(const Vector2D &screen_offset) override;
	void Finalize() override;
	//~ End GameObject interface

	void UpdateAnimation() override;
	void OnHitBoxCollision(const GameObject *hit_object, const BoxCollisionParams &hit_collision_params);

protected:
	void ApplyDamage(int damage) override;
	void OnDamaged(int damage) override;

private:
	// IDLE��ԃA�j���[�V�������
	const static int max_idle_flame = 1;
	int graphic_handle_idle[max_idle_flame] = {0};
	int graphic_idle_flame = 0;

	// RUN��ԃA�j���[�V�������
	const static int max_run_flame = 4;
	const static int run_flame_delay = 15; // ���̑���t���[���ɓ���܂ł̎���
	int run_flame_adjust = 0;			   // delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphic_handle_run[max_run_flame] = {0, 0, 0, 0};
	int graphic_run_flame = 0;

	// DEAD��ԃA�j���[�V�������
	const static int max_damage_flame = 1;
	int graphic_handle_damage[max_damage_flame] = {0};
	int graphic_damage_flame = 0;
};
