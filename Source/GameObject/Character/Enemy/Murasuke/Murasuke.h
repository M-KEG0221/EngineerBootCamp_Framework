#pragma once
#include "../Enemy.h"
class Murasuke :public Enemy
{
public:
	Murasuke();
	virtual ~Murasuke();
public:
	//~ Begin GameObject interface
	void Initialize() override;
	void Update(float delta_seconds) override;
	void Draw(const Vector2D& screen_offset) override;
	void Finalize() override;
	//~ End GameObject interface

	void UpdateAnimation() override;

private:
	//IDLE状態アニメーション情報
	const static int max_idle_flame = 1;
	int graphic_handle_idle[max_idle_flame] = { 0 };
	int graphic_idle_flame = 0;

	//RUN状態アニメーション情報
	const static int max_run_flame = 4;
	const static int run_flame_delay = 15;// 次の走りフレームに入るまでの時間
	int run_flame_adjust = 0;// delayかけてフレーム遷移するための値
	int graphic_handle_run[max_run_flame] = { 0,0,0,0 };
	int graphic_run_flame = 0;
};

