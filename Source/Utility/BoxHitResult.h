#pragma once
struct BoxHitResult
{
	bool is_hit_left_side = false;
	bool is_hit_right_side = false;
	bool is_hit_top_side = false;
	bool is_hit_under_side = false;

	bool IsHit() { return is_hit_left_side || is_hit_right_side || is_hit_top_side || is_hit_under_side; }
};

