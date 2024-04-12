#include "Dxlib.h"

#include "BoxCollisionParams.h"
#include "Vector2D.h"

// FIXME: 横移動してる敵と接し続けると上下移動ができない＆床or天井と接する状態で下or上入力しながら横移動ができない
BoxCollisionParams::BoxCollisionParams(CollisionObjectType collision_object_type, CollisionType collision_type, Vector2D box_size, boolean can_hit)
	: collision_object_type(collision_object_type),
	  collision_type(collision_type),
	  box_size(box_size),
	  hit_object_types(0),
	  can_hit(can_hit)
{
}

BoxCollisionParams::~BoxCollisionParams()
{
}

void BoxCollisionParams::Update(float delta_seconds, Vector2D object_position)
{
	SetOldCenterPosition(GetCenterPosition());

	SetCenterPosition(object_position);
}

void BoxCollisionParams::Draw(const Vector2D &screen_offset)
{
	int x1, y1;
	center_position.ToInt(x1, y1);

	int x2, y2;
	box_size.ToInt(x2, y2);

	can_hit
		? DrawBox(x1, y1, x1 + x2, y1 + y2, color, false)
		: DrawBox(x1, y1, x1 + x2, y1 + y2, falseColor, false);
}

bool BoxCollisionParams::IsHitCheckTarget(BoxCollisionParams other_collision) const
{

	float x = center_position.x;
	float y = center_position.y;
	float width = box_size.x;
	float height = box_size.y;
	float old_x = old_center_position.x;
	float old_y = old_center_position.y;

	float other_x = other_collision.center_position.x;
	float other_y = other_collision.center_position.y;
	float other_width = other_collision.box_size.x;
	float other_height = other_collision.box_size.y;

	float other_under = other_y + other_height;
	float other_right = other_x + other_width;

	DrawBox(x, y, x + width, y + height, GetColor(0, 0, 255), false);

	return (can_hit && other_collision.GetCanHit()) && ((
			x <= other_right &&
			x + width >= other_x &&
			y <= other_under &&
			y + height >= other_y
			) ||
			((old_y <= other_y) && (y >= other_under))); // ゲームウィンドウから離れた時、離れた時間＊重力分落下するのを防ぐ
}

BoxHitResult BoxCollisionParams::HitCheckTarget(BoxCollisionParams other_collision) const
{

	float x = center_position.x;
	float y = center_position.y;
	float width = box_size.x;
	float height = box_size.y;
	float old_x = old_center_position.x;
	float old_y = old_center_position.y;

	float other_x = other_collision.center_position.x;
	float other_y = other_collision.center_position.y;
	float other_width = other_collision.box_size.x;
	float other_height = other_collision.box_size.y;
	float other_old_x = other_collision.GetOldCenterPosition().x;
	float other_old_y = other_collision.GetOldCenterPosition().y;

	float other_under = other_y + other_height;
	float other_right = other_x + other_width;

	BoxHitResult result;
	// めり込み確認
	result.is_hit_left_side =
		(old_x >= other_right) && (x < other_right);
	result.is_hit_right_side =
		(old_x + width <= other_x) && (x + width > other_x);
	result.is_hit_top_side =
		(old_y >= other_under) && (y < other_under);
	result.is_hit_under_side =
		(old_y + height <= other_y) && (y + height > other_y);

	// 接触
	result.is_touch_left_side =
		x == other_right && y;
	result.is_touch_right_side =
		x + width == other_x;
	result.is_touch_top_side =
		y == other_under;
	result.is_touch_under_side =
		y + height == other_y;

	// printfDx("<%f,", y + height);
	// printfDx("%f>\n", other_y);

	/*printfDx("X<%f,", x);
	printfDx("%f>\n", other_right);
	printfDx("Y<%f,", y + height);
	printfDx("%f>\n", other_y);
	printfDx("---\n");*/

	return result;
}