#pragma once
#include "../GameObject.h"

/**
 * �L�����N�^�[
 * �T���v���p�ɊȈՓI�Ɏ���
 */
class Character abstract : public GameObject
{
protected:
	enum class DirectionState
	{
		LEFT, RIGHT,
	};

	enum class AnimationState
	{
		IDLE, RUN, JUMP, ATTACK, DAMAGED, DEAD
	};

public:
	Character();
	virtual ~Character();

public:
	//~ Begin Character interface
	virtual void Initialize() override;
	virtual void Update(float delta_seconds) override;
	virtual void Draw(const Vector2D& screen_offset) override;
	virtual void Finalize() override;
	//~ End Character interface

	DirectionState GetCurrentDirectionState() { return current_direction_state; }

protected:
	int hp;
	int graphic_handle;
	const float GRAVITY = 1480.0f;//�K��
	const float MAX_FALL_SPEED = 1000.0f;//�K��

	//�L�����̌����֌W
	DirectionState current_direction_state;
	void SetCurrentDirectionState(DirectionState d) { current_direction_state = d; }

	void ApplyDamage(int damage) {};
	virtual void UpdateAnimation() {};
	virtual void OnDamaged(int damage) {};
private:
	//virtual void onDamaged(int damage) {};
};

