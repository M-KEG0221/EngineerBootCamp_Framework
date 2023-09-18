#include "DxLib.h"

#include "BoxCollisionParams.h"
#include "Vector2D.h"

//FIXME: ‰¡ˆÚ“®‚µ‚Ä‚é“G‚ÆÚ‚µ‘±‚¯‚é‚Æã‰ºˆÚ“®‚ª‚Å‚«‚È‚¢•°or“Vˆä‚ÆÚ‚·‚éó‘Ô‚Å‰ºorã“ü—Í‚µ‚È‚ª‚ç‰¡ˆÚ“®‚ª‚Å‚«‚È‚¢
BoxCollisionParams::BoxCollisionParams(CollisionObjectType collision_object_type, CollisionType collision_type, Vector2D box_extent)
	:
	collision_object_type(collision_object_type),
	collision_type(collision_type),
	box_extent(box_extent),
	hit_object_types(0)//ˆá‚¤‰Â”\«
{
}

BoxCollisionParams::~BoxCollisionParams()
{
}

void BoxCollisionParams::Update(float delta_seconds, Vector2D object_position, Vector2D position_adjust)
{
	SetOldCenterPosition(GetCenterPosition());

	SetCenterPosition(object_position + position_adjust);
}

void BoxCollisionParams::Draw(const Vector2D& screen_offset)
{
	int x1, y1;
	center_position.ToInt(x1, y1);

	int x2, y2;
	box_extent.ToInt(x2, y2);

	DrawBox(x1, y1, x1 + x2, y1 + y2, color, false);

	char str[256];
	sprintf_s(str, sizeof(str), "x: %d, y: %d", x1, y1);
}

bool BoxCollisionParams::IsHitCheckTarget(BoxCollisionParams other_collision)const
{
	int x, y, width, height;
	center_position.ToInt(x, y);
	box_extent.ToInt(width, height);

	int other_x, other_y, other_width, other_height;
	other_collision.center_position.ToInt(other_x, other_y);
	other_collision.box_extent.ToInt(other_width, other_height);

	return
		x < other_x + other_width &&
		x + width > other_x &&
		y < other_y + other_height &&
		y + height > other_y;
}

BoxHitResult BoxCollisionParams::HitCheckTarget(BoxCollisionParams other_collision)const
{
	int x, y,
		width, height,
		old_x, old_y;
	center_position.ToInt(x, y);
	box_extent.ToInt(width, height);
	old_center_position.ToInt(old_x, old_y);

	int other_x, other_y,
		other_width, other_height,
		other_old_x, other_old_y;
	other_collision.center_position.ToInt(other_x, other_y);
	other_collision.box_extent.ToInt(other_width, other_height);
	other_collision.GetOldCenterPosition().ToInt(other_old_x, other_old_y);
	int other_right = other_x + other_width;
	int other_old_right = other_old_x + other_width;
	int other_under = other_y + other_height;
	int other_old_under = other_old_y + other_height;

	BoxHitResult result;
	result.is_hit_left_side =
		(old_x > other_right/* || x > other_old_right*/) && (x < other_right);
	result.is_hit_right_side =
		(old_x + width < other_x /*|| x + width < other_old_x*/) && (x + width > other_x);
	result.is_hit_top_side =
		(old_y > other_under /*|| y > other_old_under*/) && (y < other_under);
	result.is_hit_under_side =
		(old_y + height < other_y /*|| y + height < other_old_y*/) && (y + height > other_y);

	char str[256];
	sprintf_s(
		str, sizeof(str), "¶%d, %d:%d   \n‰E%d, %d:%d   \nã%d, %d:%d   \n‰º%d, %d:%d",
		old_x > other_right, x < other_right, result.is_hit_left_side,
		old_x + width < other_x, x + width > other_x, result.is_hit_right_side,
		old_y > other_under, y < other_under, result.is_hit_top_side,
		old_y + height < other_y, y + height > other_y, result.is_hit_under_side
	);
	//DrawString(0, 40, str, GetColor(0, 255, 0));
	//prwintfDx(str);

	return result;
}