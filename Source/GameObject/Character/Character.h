#pragma once
#include "../GameObject.h"

/**
 * キャラクター
 * サンプル用に簡易的に実装
 */
class Character abstract : public GameObject
{
protected:
	enum class DirectionState
	{
		LEFT,
		RIGHT,
	};

	enum class AnimationState
	{
		IDLE,
		RUN,
		JUMP,
		ATTACK,
		DAMAGED,
		DEAD
	};

public:
	Character();
	Character(SceneBase* owner_scene);
	virtual ~Character();

public:
	//~ Begin Character interface
	virtual void Initialize() override;
	virtual void Update(float delta_seconds) override;
	virtual void Draw(const Vector2D &screen_offset) override;
	virtual void Finalize() override;
	//~ End Character interface

	DirectionState GetCurrentDirectionState() { return current_direction_state; }

protected:
	int hp;
	int graphic_handle;
	const float GRAVITY = 1480.0f;		  // 適当
	const float MAX_FALL_SPEED = 1000.0f; // 適当

	// 攻撃の判定
	BoxCollisionParams *attack_collision;

	// キャラの向き関係
	DirectionState current_direction_state;
	void SetCurrentDirectionState(DirectionState d) { current_direction_state = d; }
	// virtual void UpdateCollisions(float delta_seconds) override;

	/**
	 * デバッグ用
	 * コリジョンを全て描画する
	 */
	virtual void DrawCollisions(Vector2D const screen_offset){};

	/**
	 * 自分自身にダメージを与える
	 */
	virtual void ApplyDamage(int damage){};

	/**
	 * 自分がダメージを受けた時の処理（
	 */
	virtual void OnDamaged(int damage){};

	virtual void UpdateAnimation(){};

	virtual void UpdateCollisions(float delta_seconds){};

private:
	// virtual void OnDamaged(int damage){};
};
