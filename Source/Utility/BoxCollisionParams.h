#pragma once
#include "Vector2D.h"
#include "BoxHitResult.h"
#include "DxLib.h"

struct BoxCollisionParams
{
	enum class CollisionObjectType
	{
		GROUND = 1,
		PLAYER = 2,
		ENEMY = 4,
		ITEM = 8,
	};

	enum class CollisionType
	{
		BLOCK,//���蔲���Ȃ��H
		OVERLAP,//���蔲������
	};
public:
	void Update(float delta_seconds, Vector2D object_position, Vector2D position_adjust = Vector2D(0, 0));
	void Draw(const Vector2D& screen_offset);
	/**
	* @params collision_object_type �I�u�W�F�N�g�̎��
	* @params collision_type �R���W�����̎��
	* @params box_extent �R���W�����i�����`�j�͈̔� ���ӂƒZ�ӂ̒��S����̒���������
	*/
	BoxCollisionParams(CollisionObjectType collision_object_type, CollisionType collision_type, Vector2D box_entent);
	~BoxCollisionParams();

	//�R���W�����̈ʒu�i����j
	Vector2D center_position;
	Vector2D GetCenterPosition()const { return center_position; }
	void SetCenterPosition(Vector2D new_position) { center_position = new_position; }

	//���̃R���W�����̈ʒu
	Vector2D old_center_position;
	Vector2D GetOldCenterPosition() { return old_center_position; }
	void SetOldCenterPosition(Vector2D new_old_position) { old_center_position = new_old_position; }

	CollisionObjectType collision_object_type;
	CollisionObjectType GetCollisionObjectType()const { return collision_object_type; }

	CollisionType collision_type;
	CollisionType GetCollisionType()const { return collision_type; };

	bool IsHitCheckTarget(BoxCollisionParams other_collision) const;
	BoxHitResult HitCheckTarget(BoxCollisionParams other_collision) const;

	unsigned int hit_object_types;//�������g�ɓ��������R���W�����̃^�C�v�H
	Vector2D box_extent;//�R���W�����͈̔́iextent: �͈́j�@���ix�j�Əc�iy�j
	Vector2D GetBoxExtent()const { return box_extent; }

	int color = GetColor(255, 0, 0);
};

