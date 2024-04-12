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
	const float GRAVITY = 1480.0f;		  // �K��
	const float MAX_FALL_SPEED = 1000.0f; // �K��

	// �U���̔���
	BoxCollisionParams *attack_collision;

	// �L�����̌����֌W
	DirectionState current_direction_state;
	void SetCurrentDirectionState(DirectionState d) { current_direction_state = d; }
	// virtual void UpdateCollisions(float delta_seconds) override;

	/**
	 * �f�o�b�O�p
	 * �R���W������S�ĕ`�悷��
	 */
	virtual void DrawCollisions(Vector2D const screen_offset){};

	/**
	 * �������g�Ƀ_���[�W��^����
	 */
	virtual void ApplyDamage(int damage){};

	/**
	 * �������_���[�W���󂯂����̏����i
	 */
	virtual void OnDamaged(int damage){};

	virtual void UpdateAnimation(){};

	virtual void UpdateCollisions(float delta_seconds){};

private:
	// virtual void OnDamaged(int damage){};
};
