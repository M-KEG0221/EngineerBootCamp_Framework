#pragma once
struct BoxHitResult
{
	bool is_hit_left_side = false;
	bool is_hit_right_side = false;
	bool is_hit_top_side = false;
	bool is_hit_under_side = false;

	bool is_touch_left_side = false;
	bool is_touch_right_side = false;
	bool is_touch_top_side = false;
	bool is_touch_under_side = false;

	bool IsHit() {
		return is_hit_left_side
			|| is_hit_right_side
			|| is_hit_top_side
			|| is_hit_under_side
			|| is_touch_left_side
			|| is_touch_right_side
			|| is_touch_top_side
			|| is_touch_under_side;
	}

	bool IsTouchVerticalSide() { return is_touch_under_side || is_touch_top_side; }
	bool IsTouchHorizontalSide() { return is_touch_left_side || is_touch_right_side; }
};

