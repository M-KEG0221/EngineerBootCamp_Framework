#pragma once
#include "../GameObject.h"

/**
 * サンプルオブジェクト
 * サンプル用に簡易的に実装
 */
class Character : public GameObject
{
public:
	Character();
	virtual ~Character();

public:
	//~ Begin GameObject interface
	virtual void Initialize() override;
	void Update(float delta_seconds) override;
	void Draw(const Vector2D& screen_offset) override;
	void Finalize() override;
	//~ End GameObject interface

private:
	const static int idleMaxFlame = 4;
	const static int idleFlameDelay = 120;// まばたきアニメーションに入るまでの時間
	int flame_adjust = 0;// delayかけてフレーム遷移するための値
	int graphic_handle_idle[idleMaxFlame];
	int graphic_idle_flame;

	int hp;
};

