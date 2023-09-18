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
		BLOCK,//すり抜けなし？
		OVERLAP,//すり抜けあり
	};
public:
	void Update(float delta_seconds, Vector2D object_position, Vector2D position_adjust = Vector2D(0, 0));
	void Draw(const Vector2D& screen_offset);
	/**
	* @params collision_object_type オブジェクトの種類
	* @params collision_type コリジョンの種類
	* @params box_extent コリジョン（長方形）の範囲 長辺と短辺の中心からの長さを入れる
	*/
	BoxCollisionParams(CollisionObjectType collision_object_type, CollisionType collision_type, Vector2D box_entent);
	~BoxCollisionParams();

	//コリジョンの位置（左上）
	Vector2D center_position;
	Vector2D GetCenterPosition()const { return center_position; }
	void SetCenterPosition(Vector2D new_position) { center_position = new_position; }

	//元のコリジョンの位置
	Vector2D old_center_position;
	Vector2D GetOldCenterPosition() { return old_center_position; }
	void SetOldCenterPosition(Vector2D new_old_position) { old_center_position = new_old_position; }

	CollisionObjectType collision_object_type;
	CollisionObjectType GetCollisionObjectType()const { return collision_object_type; }

	CollisionType collision_type;
	CollisionType GetCollisionType()const { return collision_type; };

	bool IsHitCheckTarget(BoxCollisionParams other_collision) const;
	BoxHitResult HitCheckTarget(BoxCollisionParams other_collision) const;

	unsigned int hit_object_types;//自分自身に当たったコリジョンのタイプ？
	Vector2D box_extent;//コリジョンの範囲（extent: 範囲）　横（x）と縦（y）
	Vector2D GetBoxExtent()const { return box_extent; }

	int color = GetColor(255, 0, 0);
};

