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
		BLOCK,	 // すり抜けなし？
		OVERLAP, // すり抜けあり
	};

public:
	void Update(float delta_seconds, Vector2D object_position);
	void Draw(const Vector2D &screen_offset);
	/**
	 * @params collision_object_type オブジェクトの種類
	 * @params collision_type コリジョンの種類
	 * @params box_extent コリジョン（長方形）の範囲 長辺と短辺の中心からの長さを入れる
	 */
	BoxCollisionParams(CollisionObjectType collision_object_type, CollisionType collision_type, Vector2D box_size, boolean can_hit = true);
	~BoxCollisionParams();

	// コリジョンの位置（左上）
	Vector2D center_position;
	Vector2D GetCenterPosition() const { return center_position; }
	void SetCenterPosition(Vector2D new_position) { center_position = new_position; }

	// 1f前のコリジョンの位置
	Vector2D old_center_position;
	Vector2D GetOldCenterPosition() const { return old_center_position; }
	void SetOldCenterPosition(Vector2D new_old_position) { old_center_position = new_old_position; }

	CollisionObjectType collision_object_type;
	CollisionObjectType GetCollisionObjectType() const { return collision_object_type; }

	CollisionType collision_type;
	CollisionType GetCollisionType() const { return collision_type; };
	void SetCollisionType(CollisionType new_collision_type) { collision_type = new_collision_type; }

	bool IsHitCheckTarget(BoxCollisionParams other_collision) const;
	BoxHitResult HitCheckTarget(BoxCollisionParams other_collision) const;

	unsigned int hit_object_types; // 自分自身に当たったコリジョンのタイプ？
	Vector2D box_size;			   // コリジョンの範囲（extent: 範囲）　横（x）と縦（y）
	Vector2D GetBoxSize() const { return box_size; }

	boolean can_hit;
	boolean GetCanHit() const { return can_hit; }
	void SetCanHit(boolean new_can_hit) { can_hit = new_can_hit; }

	int color = GetColor(255, 0, 0);
	int falseColor = GetColor(200, 200, 255);

private:
	// コリジョンの持ち主のポジション（描画位置）からの距離
	// Vector2D delta_position;
};
