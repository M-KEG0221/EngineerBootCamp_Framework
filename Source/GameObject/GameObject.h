#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/BoxCollisionParams.h"

/**
 * �Q�[�����ɕ\�������I�u�W�F�N�g�̊��N���X
 */
class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {}

public:
	/**
	 * ������
	 */
	virtual void Initialize() {}

	/**
	 * �X�V
	 * @param	delta_seconds	�O�t���[���Ƃ̍�������(s)
	 */
	virtual void Update(float delta_seconds) {}

	/**
	 * �`��
	 */
	virtual void Draw(const Vector2D& screen_offset) {}

	/**
	 * ���
	 */
	virtual void Finalize() {}

	/**
	 * �V�[���̎擾
	 * @return owner_scene
	 */
	class SceneBase* GetOwnerScene() const { return owner_scene; }

	/**
	 * �V�[���̃Z�b�g
	 * @param	new_owner_scene	�Z�b�g����Position
	 */
	void SetOwnerScene(class SceneBase* new_owner_scene);

	/**
	 * Position�̎擾
	 * @return	position
	 */
	Vector2D GetPosition() const { return position; }

	/**
	 * Position�̃Z�b�g
	 * @param	new_position	�Z�b�g����Position
	 */
	void SetPosition(const Vector2D& new_position);

	/**
	 * OldPosition�̎擾
	 * @return	old_position
	 */
	Vector2D GetOldPosition() const { return old_position; }

	/**
	 * OldPosition�̃Z�b�g
	 * @param	new_old_position	�Z�b�g����Position
	 */
	void SetOldPosition(const Vector2D& new_old_position);
	/**
	 * �`�揇�̎擾
	 * @return	draw_sort_priority
	 */
	int GetDrawSortPriority() const { return draw_sort_priority; }

	/**
	 * �`�揇�̃Z�b�g
	 * @param	new_priority	�Z�b�g����`�揇
	 */
	void SetDrawSortPriority(int new_priority);

	BoxCollisionParams* GetBodyCollision() { return body_collision; }

	virtual void OnHitBoxCollision(const GameObject* hit_object, const BoxCollisionParams& hit_collision_params) {};
	virtual void OnNoHitBoxCollision() {};
	void ResetHitResult() { hitResult = BoxHitResult(); }

protected:
	// �ʒu
	Vector2D position;

	// 1f�O�̈ʒu
	Vector2D old_position;

	//�R���W����
	BoxCollisionParams* body_collision;
	BoxHitResult hitResult;

	//�摜�̕`��ʒu�ƃR���W�����̕`��ʒu�̍���
	Vector2D delta_position = Vector2D(0, 0);
	Vector2D GetDeltaPosition() { return delta_position; }
	void SetDeltaPosition(Vector2D new_delta_position) { delta_position = new_delta_position; };

private:
	// �I�[�i�[�ƂȂ�V�[��
	class SceneBase* owner_scene;

	// �`�揇�B���l��������������`����s��
	int draw_sort_priority;
};